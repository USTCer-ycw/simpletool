#include "src/isutility/Semaphore.h"

using namespace istool::isutility;

Semaphore::Semaphore(int count)
	:count_(count)
{
}
Semaphore::~Semaphore()
{

}
void Semaphore::wait()
{
	std::unique_lock<std::mutex> lock(mutex_);
	if (--count_ < 0)
	{
		condition_.wait(lock);
	}
}
void Semaphore::signal()
{
	std::unique_lock<std::mutex> lock(mutex_);
	if (++count_ <= 0)
	{
		condition_.notify_one();
	}
}
