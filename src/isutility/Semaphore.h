#ifndef ISTOOL_ISUTILITY_SEMAPHORE_H
#define ISTOOL_ISUTILITY_SEMAPHORE_H
#include <src/isutility/Compatible.h>
#include<mutex>
#include<condition_variable>

//PV操作对于每一个进程来说，都只能进行一次，而且必须成对使用。
namespace istool
{
	namespace isutility
	{
		class Semaphore
		{
		public:
			Semaphore(int count = 1);
			~Semaphore();
			void wait();
			void signal();
		private:
			int count_;
			std::mutex mutex_;
			std::condition_variable condition_;
		};
	}
}

#endif  

