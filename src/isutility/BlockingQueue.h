// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef ISTOOL_ISUTILITY_BLOCKINGQUEUE_H
#define ISTOOL_ISUTILITY_BLOCKINGQUEUE_H

#include <assert.h>
#include <deque>
#include <functional>

#include <src/isutility/Mutex.h>
#include <src/isutility/Condition.h>
#include <src/isutility/NonCopyAble.h>

namespace istool
{
	namespace isutility
	{
		template<typename T>
		class BlockingQueue : isutility::NonCopyable
		{
		public:
			BlockingQueue()
				: notEmpty_(mutex_),
				queue_()

			{
			}


			void put(T&& x)
			{
				MutexLockGuard lock(mutex_);
				queue_.push_back(std::move(x));
				notEmpty_.notify();
			}


			T take()
			{
				MutexLockGuard lock(mutex_);
				// always use a while-loop, due to spurious wakeup
				while (queue_.empty())
				{
					notEmpty_.wait();
				}
				//assert(!queue_.empty());
				if (queue_.empty())
				{
					return T();
				}

				T front(std::move(queue_.front()));

				queue_.pop_front();
				return front;
			}

			size_t size() const
			{
				MutexLockGuard lock(mutex_);
				return queue_.size();
			}

			void terminate()
			{
				MutexLockGuard lock(mutex_);
				notEmpty_.notifyAll();
			}
		private:
			mutable MutexLock mutex_;
			Condition         notEmpty_;
			std::deque<T>     queue_;
			int milliseconds_;
		};
	}
}

#endif  
