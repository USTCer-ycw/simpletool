#ifndef ISTONE_UTILITY_FLOW_H_
#define ISTONE_UTILITY_FLOW_H_

#include<atomic>
#include"src/utility/Compatible.h"
#include "src/utility/CacheNodeList.h"

using namespace std;

namespace istone
{
	namespace utility
	{			
		template<typename T>	class FlowReader;
		template<typename T>
		class Flow
		{
			friend class FlowReader<T>;
			struct node
			{
				node* next;
				T value;
			};
		public:
			Flow()
			{
				init();
			}
			~Flow()
			{
				release();
			}
			void write(T v)
			{
				node* n = new node;
				n->next = nullptr;
				n->value = v;
				tail_->next = n;
				tail_ = n;
				__memory_barrier();
				++count_;
			}
			long count() const
			{
				return count_.load();
			}
			bool empty() const
			{
				return count_.load() == 0;
			}
			node* head()
			{
				return head_;
			}
			void clear()
			{
				release();
				init();
			}
			char* allocate(unsigned int length)
			{
				return cacheList_->allocate(length);
			}
		private:
			void init()
			{
				node* n = new node;
				n->next = nullptr;
				tail_ = head_ = n;
				count_.store(0);
				cacheList_ = new CacheNodeList();
			}
			void release()
			{
				node* n = head_;
				do
				{
					node* next = n->next;
					delete n;
					n = next;
				} while (n);
				delete cacheList_;
			}

		private:
			atomic<long> count_;
			node* tail_; // tail of the queue 	
			node* head_; // head of the queue 			
			CacheNodeList *cacheList_;
		};
	}
}
#endif
