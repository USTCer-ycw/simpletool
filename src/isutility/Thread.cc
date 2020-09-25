#include <src/isutility/Thread.h>
#include <src/isutility/CurrentThread.h>
#include <src/isutility/Compatible.h>
#include <src/isutility/Logging.h>
#include <system_error>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>

#pragma warning(disable:4101)
namespace istool
{
	namespace currentthread
	{

		thread_local uint64_t t_cachedTid = 0;
		thread_local char t_tidString[32];
		thread_local int t_tidStringLength = 6;
		thread_local const char* t_threadName = "unknown";
		const bool sameType = std::is_same<int, std::thread::id>::value;
		static_assert(sameType == false, "not same");

	}

	namespace detail
	{

		uint64_t gettid()
		{

#ifdef __LINUX__
			return static_cast<uint64_t>(::syscall(SYS_gettid));
#endif
#ifdef WIN32
			return ::GetCurrentThreadId();
#endif
		}


		struct ThreadData
		{
			typedef istool::Thread::ThreadFunc ThreadFunc;
			ThreadFunc func_;
			string name_;
			std::weak_ptr<uint64_t> wkTid_;

			ThreadData(const ThreadFunc& func,
				const string& name,
				const std::shared_ptr<uint64_t>& tid)
				: func_(func),
				name_(name),
				wkTid_(tid)
			{ }

			void runInThread()
			{
				uint64_t tid = istool::currentthread::tid();

				std::shared_ptr<uint64_t> ptid = wkTid_.lock();
				if (ptid)
				{
					*ptid = tid;
					ptid.reset();
				}

				istool::currentthread::t_threadName = name_.empty() ? "ftmdThread" : name_.c_str();
				//给线程命名
#ifdef __LINUX__
				::prctl(PR_SET_NAME, istool::currentthread::t_threadName);
#endif
				func_();
				istool::currentthread::t_threadName = "finished";
			}
		};

		void* startThread(void* obj)
		{
			ThreadData* data = static_cast<ThreadData*>(obj);
			data->runInThread();
			delete data;
			return NULL;
		}

	}
}

using namespace istool;

void currentthread::cacheTid()
{
	if (t_cachedTid == 0)
	{
		t_cachedTid = detail::gettid();
		t_tidStringLength = SNPRINTF(t_tidString, sizeof t_tidString, "%5llu", t_cachedTid);
	}
}

bool currentthread::isMainThread()
{
	return tid() == ::GETPID();
}

void currentthread::sleepUsec(int64_t usec)
{
#ifdef __LINUX__
	struct timespec ts = { 0, 0 };
	ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
	ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
	::nanosleep(&ts, NULL);
#endif
#ifdef WIN32
	::Sleep((DWORD)(usec >= 1000 ? usec / 1000 : 1 ));
#endif
}

std::atomic<int32_t> Thread::numCreated_;


Thread::Thread(ThreadFunc&& func, const string& n)
	: started_(false),
	joined_(false),
	pthreadId_(nullptr),
	tid_(new uint64_t(0)),
	func_(std::move(func)),
	name_(n)
{
	setDefaultName();
}



Thread::~Thread()
{
	if (started_ && !joined_)
	{
		pthreadId_->detach();
	}
}

void Thread::setDefaultName()
{
	int num = numCreated_++;
	if (name_.empty())
	{
		char buf[32];
		SNPRINTF(buf, sizeof buf, "Thread%d", num);
		name_ = buf;
	}
}

void Thread::start()
{
	assert(!started_);
	started_ = true;
	// FIXME: move(func_)
	detail::ThreadData* data = new detail::ThreadData(func_, name_, tid_);
	try {
		std::shared_ptr<std::thread> newId(new std::thread(&detail::startThread, data));
		pthreadId_.swap(newId);
	}
	catch (std::system_error *pError)
	{
		//LOG_SYSFATAL << "Failed in pthread_create";
	}

}

void Thread::join()
{
	assert(started_);
	assert(!joined_);
	joined_ = true;
	return pthreadId_->join();
}

