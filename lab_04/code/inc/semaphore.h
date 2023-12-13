#pragma once

#include <mutex>
#include <condition_variable>

using namespace std;

class Semaphore {
public:
	Semaphore (int count = 0) : _count(count) {}

	inline void notify() {
		std::unique_lock<std::mutex> lock(_mtx);
		_count++;
		_cv.notify_one();
	}

	inline void wait() {
		std::unique_lock<std::mutex> lock(_mtx);

		while(!_count)
			_cv.wait(lock);
		_count--;
	}

private:
	mutex _mtx;
	condition_variable _cv;
	int _count;
};