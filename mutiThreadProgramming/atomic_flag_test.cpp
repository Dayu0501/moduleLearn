#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h>

using namespace std;

atomic_flag lock = ATOMIC_FLAG_INIT;

void f(int n) {
	while(lock.test_and_set(memory_order_acquire))
		cout << "Waiting from thread " << n << " spinning..." << endl;
	cout << "Thread " << n << " starts working" << endl;
}

void g(int n) {
	cout << "Thread " << n << " is going to start." << endl;
	lock.clear();
	cout << "Thread " << n << " starts working" << endl;
}

int main() {
	lock.test_and_set();

	thread t1(f, 1);

	thread t2(g, 2);

	t1.join();
	usleep(100);
	t2.join();

    return 0;
}