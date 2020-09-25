#ifndef ISTONE_UTILITY_CACHENODE_H
#define ISTONE_UTILITY_CACHENODE_H
#include <src/utility/Compatible.h>

namespace istone
{
	namespace utility
	{
		class CacheNode
		{
		public:
			CacheNode(unsigned int size = 10 * 1024 * 1024);
			~CacheNode();
			char* allocate(unsigned int length);
			CacheNode* getNext();
			void setNext(CacheNode* next);
			unsigned int availableSize();
		private:
			unsigned int totalSize_;
			unsigned int availableSize_;
			char *headPtr_;
			char *availablePtr_;
			CacheNode *next_;
		};
	}

}

#endif  

