#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

#if 0
int x, y = 0;

void func1() {
	x = 1;
	y = 2;
}

void func2() {
	if (y == 2) {
		x = 3;
		y = 4;
	}
}
#endif

class testClass {
public:
	int val;
	char buff[1024];
};

#if 1

int x = 0;
atomic<int> y;
atomic<testClass> gTest;

struct A {
	int a[100];
};
struct B {
	int x, y;
};

/* memory_order_acquire是对内存的写操作 */
void func1() {
	x = 1;
	y.store(2, memory_order_relaxed);
}

void func2() {
	if (y.load(memory_order_acquire) == 2) {
		x = 3;
		y.store(4, memory_order_relaxed);
	}
}

#endif

int main() {
	thread ins1{func1};
	thread ins2{func2};

	ins1.join();
	ins2.join();

	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	/* 下面的返回值1代表无锁，0代表有锁 */
	cout << "y lock = " << y.is_lock_free() << endl;

	/* 在atomic封装自定义类型的时候，编译命令如下
	 * g++ atomic_test.cpp -std=c++11 -lpthread -latomic
	 * */
	cout << "gTest lock = " << gTest.is_lock_free() << endl;


	/* atomic self define class */
	std::cout << std::boolalpha
	          << "std::atomic<A> is lock free? "
	          << std::atomic<A>{}.is_lock_free() << '\n'
	          << "std::atomic<B> is lock free? "
	          << std::atomic<B>{}.is_lock_free() << '\n';

	return 0;
}
