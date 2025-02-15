// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef ISTOOL_ISUTILITY_CONDITION_H
#define ISTOOL_ISUTILITY_CONDITION_H
#include <thread>
#include <src/isutility/Mutex.h>
#include <condition_variable>
#include <src/isutility/NonCopyAble.h>

namespace istool
{
	class Condition : isutility::NonCopyable
	{
	public:
		explicit Condition(MutexLock & mutex)
			: mutex_(mutex)
		{
		}

		~Condition()
		{
		}

		void wait()
		{
			MutexLock::UnassignGuard ug(mutex_);
			std::unique_lock<std::mutex> lck(mutex_.getPthreadMutex(), std::defer_lock);
			pcond_.wait(lck);
		}

		// returns true if time out, false otherwise.
		bool waitForSeconds(int seconds)
		{
			MutexLock::UnassignGuard ug(mutex_);
			std::unique_lock<std::mutex> lck(mutex_.getPthreadMutex(), std::defer_lock);
			return  std::cv_status::timeout == pcond_.wait_for(lck, std::chrono::seconds(seconds));
		}

		bool waitForMilliSeconds(int milliseconds)
		{
			MutexLock::UnassignGuard ug(mutex_);
			std::unique_lock<std::mutex> lck(mutex_.getPthreadMutex(), std::defer_lock);
			return  std::cv_status::timeout == pcond_.wait_for(lck, std::chrono::milliseconds(milliseconds));
		}
		void notify()
		{
			pcond_.notify_one();
		}

		void notifyAll()
		{
			pcond_.notify_all();
		}

	private:
		MutexLock  &mutex_;
		std::condition_variable pcond_;
	};

}
#endif
