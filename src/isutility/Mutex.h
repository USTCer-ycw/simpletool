// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef ISTOOL_ISUTILITY_MUTEX_H
#define ISTOOL_ISUTILITY_MUTEX_H

#include <src/isutility/CurrentThread.h>
#include <src/isutility/NonCopyAble.h>
#include <src/isutility/Compatible.h>
#include <mutex>
#include <assert.h>

#ifdef CHECK_PTHREAD_RETURN_VALUE

#ifdef NDEBUG
__BEGIN_DECLS
extern void __assert_perror_fail(int errnum,
	const char *file,
	unsigned int line,
	const char *function)
	__THROW __attribute__((__noreturn__));
__END_DECLS
#endif

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       if (__builtin_expect(errnum != 0, 0))    \
                         __assert_perror_fail (errnum, __FILE__, __LINE__, __func__);})

#else  // CHECK_PTHREAD_RETURN_VALUE

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       assert(errnum == 0); (void) errnum;})

#endif // CHECK_PTHREAD_RETURN_VALUE

namespace istool
{
	class MutexLock : isutility::NonCopyable
	{
	public:
		MutexLock()
			: holder_(0)
		{

		}

		~MutexLock()
		{
			assert(holder_ == 0);
		}

		// must be called when locked, i.e. for assertion
		bool isLockedByThisThread() const
		{
			return holder_ == currentthread::tid();
		}

		void assertLocked() const
		{
			assert(isLockedByThisThread());
		}

		// internal usage

		void lock()
		{
			mutex_.lock();
			assignHolder();
		}

		void unlock()
		{
			unassignHolder();
			mutex_.unlock();
		}

		std::mutex& getPthreadMutex() /* non-const */
		{
			return mutex_;
		}

	private:
		friend class Condition;

		class UnassignGuard : isutility::NonCopyable
		{
		public:
			UnassignGuard(MutexLock& owner)
				: owner_(owner)
			{
				owner_.unassignHolder();
			}

			~UnassignGuard()
			{
				owner_.assignHolder();
			}

		private:
			MutexLock& owner_;
		};

		void unassignHolder()
		{
			holder_ = 0;
		}

		void assignHolder()
		{
			holder_ = currentthread::tid();
		}

		std::mutex mutex_;
		PID_T holder_;
	};

	// Use as a stack variable, eg.
	// int Foo::size() const
	// {
	//   MutexLockGuard lock(mutex_);
	//   return data_.size();
	// }
	class MutexLockGuard : isutility::NonCopyable
	{
	public:
		explicit MutexLockGuard(MutexLock& mutex)
			: mutex_(mutex)
		{
			mutex_.lock();
		}

		~MutexLockGuard()
		{
			mutex_.unlock();
		}

	private:

		MutexLock& mutex_;
	};

}

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!
#define MutexLockGuard(x) error "Missing guard object name"

#endif  // ISTOOL_ISUTILITY_MUTEX_H
