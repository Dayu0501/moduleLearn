
// 头文件
class singleton {
public:
	static singleton* instance();
	…
private:
	static mutex lock_;
	static atomic<singleton*>
		inst_ptr_;
};

// 实现文件
mutex singleton::lock_;
atomic<singleton*>
	singleton::inst_ptr_;

singleton* singleton::instance()
{
	singleton* ptr = inst_ptr_.load(
		memory_order_acquire);
	if (ptr == nullptr) {
		lock_guard<mutex> guard{lock_};
		ptr = inst_ptr_.load(
			memory_order_relaxed);
		if (ptr == nullptr) {
			ptr = new singleton();
			inst_ptr_.store(
				ptr, memory_order_release);
		}
	}
	return inst_ptr_;
}