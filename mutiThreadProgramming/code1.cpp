#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <shared_mutex>

using namespace std;

mutex output_lock;
/* shared_mutext 在c++17才有的 */
shared_mutex shareMutex;

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

void work(condition_variable &cv, int &result) {
	/* 假装我们计算了很久 */
	this_thread::sleep_for(2s);
	result = 42;
	cv.notify_one();
}

void func(const char *name) {
	this_thread::sleep_for(100ms);
	lock_guard<mutex> guard{output_lock};
	cout << "I am thread " << name << '\n';
}

int main() {
	thread t1{func, "A"};
	thread t2{func, "B"};

	t1.join();
	t2.join();

	std::cout << std::endl << "----- [ scoped_thread test ] -----" << std::endl;

//	scoped_thread t3{func, "C"};
//	scoped_thread t4{func, "D"};

	std::cout << std::endl << "----- [ cond variable test ] -----" << std::endl;

	condition_variable cv;
	mutex cv_mut;
	int result;

	scoped_thread th{work, ref(cv), ref(result)};

	/* 处理工作... */
	cout << "I am waiting now ... \n";
	unique_lock lock{cv_mut};
	cv.wait(lock);

	cout << "Answer: " << result << '\n';

	return 0;
}