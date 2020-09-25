#ifndef ISTONE_UTILITY_FLOW_READER_H_
#define ISTONE_UTILITY_FLOW_READER_H_
#include"src/utility/Compatible.h"
#include "src/utility/Flow.h"

namespace istone
{
	namespace utility
	{		  
		template<typename T>
		class FlowReader
		{
		public:
			FlowReader(Flow<T> *flow)
			{
				flow_ = flow;
				readCount_ = 0;
				lastRead_ = flow_->head();
			}
			~FlowReader()
			{
			}
			bool seek(long number)
			{
				lastRead_ = flow_->head();
				readCount_ = 0;
				if(number > flow_->count())
				{
					return false;
				}			
				long count = 0;
				while(count < number && lastRead_->next)
				{
					count++;
					lastRead_ = lastRead_->next;
				}
				if (count != number)
				{
					lastRead_ = flow_->head();
					readCount_ = 0;
					return false;
				}
				readCount_ = number;
				return true;
			}
		
			bool read(T& v)
			{
				if (readCount_ == flow_->count())
					return false;
				if (!lastRead_->next)
					return false;
				v = lastRead_->next->value;
				lastRead_ = lastRead_->next;
				++readCount_;
				return true;
			}
			long readCount() const
			{
				return readCount_;
			}
		private:
			Flow<T> *flow_;
			int readCount_;
			typename Flow<T>::node *lastRead_;
		};
	}
}
#endif