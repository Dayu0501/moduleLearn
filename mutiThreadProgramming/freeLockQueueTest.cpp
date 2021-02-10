#include <iostream>
#include <emmintrin.h>
#include <thread>
#include <mutex>

using namespace std;

#define PUSHCOUNT 10000000
#define POPCOUNT  10000000

#define ERR_EMPTY_QUEUE -1111

struct Node {
	int data;
	Node *next;
};

struct Queue {
	Node *head;
	Node *tail;
};

void InitQueue(Queue *Q) {
	Node *node = new Node();
	node->next = nullptr;
	Q->head = Q->tail = node;
}

mutex m;

/* mutex的实现方式 */
void EnQueue0(Queue *Q, int data) {
	Node *node = new Node;
	node->data = data;
	node->next = nullptr;

	lock_guard<mutex> lock(m);
	Q->tail->next = node;
	Q->tail = node;
}

void EnQueue1(Queue *Q, int data) {
//	cout << "data is " << data << endl;

	Node *n = new Node();
	n->data = data;
	n->next = nullptr;

	Node *p = nullptr;
	do {
		p = Q->tail;
	} while (__sync_bool_compare_and_swap(&(p->next), nullptr, n) != true);

	__sync_bool_compare_and_swap(&(Q->tail), p, n);
}

/* 是EnQueue的改良版，防止在没有更新队尾指针的时候，线程异常退出，导致其他线程无法无法入队的情况 */
void EnQueue2(Queue *Q, int data) {
	Node *n = new Node;
	n->data = data;
	n->next = nullptr;

	Node *p = Q->tail;
	Node *oldP = p;
	do {
		while (p->next != nullptr)
			p = p->next;
	} while (__sync_bool_compare_and_swap(&(p->next), nullptr, n) != true);

	__sync_bool_compare_and_swap(&(Q->tail), oldP, n);
}

/* 由于每个线程都把tail移动到队尾，效率变低 */
void EnQueue3(Queue *Q, int data) {
	Node *n = new Node;
	n->data = data;
	n->next = nullptr;

	Node *tail = nullptr;
	Node *next = nullptr;
	while (true) {
		//先取一下尾指针和尾指针的next
		tail = Q->tail;
		next = tail->next;

		if (tail != Q->tail) continue; //这种是别的线程push了新的节点，而且更新了tail指针

		/* 下面是防止的是在执行上面的代码后，别的线程插入+更新或者是仅仅插入，未更新
		 * 下面这个判断条件完全包含上面的判断条件，为什么还需要上面的判断呢，
		 * 因为__sync_bool_compare_and_swap函数的执行，还是有一定的代价的
		 * */
		if (next != nullptr) {
			__sync_bool_compare_and_swap(&(Q->tail), tail, next);
			continue;
		}

		if (__sync_bool_compare_and_swap(&(tail->next), next, n))
			break;
	}

	__sync_bool_compare_and_swap(&(Q->tail), tail, n);  //置尾节点
}


//出队列
int DeQueue0(Queue *Q) {
	Node *p = nullptr;
	do {
		p = Q->head;
		if (p->next == nullptr) {
			return ERR_EMPTY_QUEUE;
		}
	} while (__sync_bool_compare_and_swap(&(Q->head), p, p->next) != true);
	return p->next->data;
}

/* 原版，我认为是错的 */
int DeQueue1(Queue *Q) {
	Node *head, *tail, *next = nullptr;
	int value;
	while (true) {
		//取出头指针，尾指针，和第一个元素的指针
		head = Q->head;
		tail = Q->tail;
		next = head->next;

		// Q->head 指针已移动，重新取 head指针
		if (head != Q->head) continue;

		// 如果是空队列
		if (head == tail && next == NULL) {
			return ERR_EMPTY_QUEUE;
		}

		//如果 tail 指针落后了
		if (head == tail && next == NULL) {
			__sync_bool_compare_and_swap(&(Q->tail), tail, next);
			continue;
		}

		//移动 head 指针成功后，取出数据
		if (__sync_bool_compare_and_swap(&(Q->head), head, next) == true) {
			value = next->data;
			break;
		}
	}
	free(head); //释放老的dummy结点
	return value;
}

int DeQueue2(Queue *Q) {
	Node *head, *tail, *next = nullptr;
	int value;
	while (true) {
		//取出头指针，尾指针，和第一个元素的指针
		head = Q->head;
		tail = Q->tail;
		next = head->next;

		if (head == Q->head && head == tail) {
			if (next == nullptr) return ERR_EMPTY_QUEUE;

			__sync_bool_compare_and_swap(&(Q->tail), tail, next);
			continue;
		}

		//移动 head 指针成功后，取出数据
		if (__sync_bool_compare_and_swap(&(Q->head), head, next) == true) {
			value = next->data;
			break;
		}
	}
	free(head); //释放老的dummy结点
	return value;
}

void startPopQ(Queue *Q) {
	for (int i = 0; i < 4 * POPCOUNT; ++i) {
		//DeQueue1(Q);
		DeQueue2(Q);
	}

//	while (1) {
//		DeQueue(Q);
//	}
}

void startPushQ(Queue *Q) {
	for (int i = 0; i < PUSHCOUNT; ++i) {
		//EnQueue0(Q, 100);
		//EnQueue1(Q, 100);
		//EnQueue2(Q, 100);
		EnQueue3(Q, 100);
	}
}

int main() {
	cout << "hello world !" << endl;
	Queue *Q = new Queue;

	InitQueue(Q);

	thread t1{startPushQ, Q};
	thread t2{startPushQ, Q};
	thread t3{startPushQ, Q};
	thread t4{startPushQ, Q};

	thread t5{startPopQ, Q};


	t1.join();
	t2.join();
	t3.join();
	t4.join();

	t5.join();

	Node *index = Q->head;
	int count = 0;
	while (index != NULL) {
//		cout << "data is " << index->data << endl;
		index = index->next;
		count++;
	}

	cout << "count is " << count << endl;
}

