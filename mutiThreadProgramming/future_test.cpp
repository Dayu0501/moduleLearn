
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

using namespace std;

class scoped_thread {
public:
	template<typename... Arg>
	scoped_thread(Arg &&... arg)
		: thread_(std::forward<Arg>(arg)...) {}

	scoped_thread(scoped_thread &&other)
		: thread_(std::move(other.thread_)) {}

	scoped_thread(const scoped_thread &) = delete;

	~scoped_thread() {
		if (thread_.joinable()) {
			thread_.join();
		}
	}

private:
	thread thread_;
};

int work() {
	// 假装我们计算了很久
	this_thread::sleep_for(2s);
	return 42;
}

int main() {
	/* async起到了线程的作用，futrue成为未来量，不是现成的作用，它起到的就是得到未来某一异步线程处理的值的作用。
	 * async 也不是真正的异步，而是封装的多线程，至于在linux下是否对posix的封装不太清楚。 */
	auto fut = async(launch::async, work);

	/* 处理工作... */
	cout << "I am waiting now\n";
	cout << "Answer: " << fut.get() << '\n';

	std::cout << std::endl << "----- [ package task ] -----" << std::endl;

	/* 把函数包装一下 */
	packaged_task<int()> task{work};
	/* 从这个包装中拿到未来量 */
	auto fut1 = task.get_future();
	/* 把这个函数包交给一个线程去执行 */
	scoped_thread th{move(task)};

	/* 处理工作... */
	this_thread::sleep_for(1s);
	cout << "I am waiting now\n";
	cout << "Answer: " << fut1.get() << '\n';
}