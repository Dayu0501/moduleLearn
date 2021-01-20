#include <atomic>

namespace mLearn {
	void Lock(std::atomic_flag *lock) {
		while(lock->test_and_set());
	}

	void UnLock(std::atomic_flag *lock) {
		lock->clear();
	}
}