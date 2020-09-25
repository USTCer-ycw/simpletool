
#ifndef ISTOOL_ISUTILITY_ASYMCLOGGING_H_
#define ISTOOL_ISUTILITY_ASYMCLOGGING_H_

#include <memory>
#include <vector>

#include <src/isutility/Thread.h>
#include <src/isutility/LogStream.h>
#include <src/isutility/NonCopyAble.h>
#include <src/isutility/Condition.h>
#include <src/isutility/CountDownLatch.h>
#include <src/isutility/Mutex.h>

using namespace istool;
using namespace istool::isutility;

namespace istool
{
	namespace isutility
	{
		class AsyncLogging : NonCopyable
		{
		public:

			AsyncLogging(const string& basename,
				size_t rollSize,
				int flushInterval = 3,
				bool usedmq = true
				);

			~AsyncLogging()
			{
				if (running_)
				{
					stop();
				}
			}
			void append(const char* logline, int len);

			void start()
			{
				running_ = true;
				thread_.start();
				latch_.wait();
			}

			void stop()
			{
				running_ = false;
				cond_.notify();
				thread_.join();
			}

		private:

			// declare but not define, prevent compiler-synthesized functions
			AsyncLogging(const AsyncLogging&);  // ptr_container
			void operator=(const AsyncLogging&);  // ptr_container

			void threadFunc();
			int publishMeseage(const char *msg, int length) const;
			typedef detail::FixedBuffer<detail::kLargeBuffer> Buffer;
			typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
			typedef std::unique_ptr<Buffer> BufferPtr;

			const int flushInterval_;
			bool running_;
			string basename_;
			size_t rollSize_;
			Thread thread_;
			CountDownLatch latch_;
			MutexLock  mutex_;
			Condition cond_;
			BufferPtr currentBuffer_;
			BufferPtr nextBuffer_;
			BufferVector buffers_;
		};
	}
}

#endif // ISTOOL_ISUTILITY_ASYMCLOGGING_H_
