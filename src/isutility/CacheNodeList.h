#ifndef ISTONE_UTILITY_CACHENODELIST_H
#define ISTONE_UTILITY_CACHENODELIST_H

#include <src/utility/CacheNode.h>

namespace istone
{
	namespace utility
	{
		class CacheNodeList
		{
		public:
			CacheNodeList(unsigned int nodeSize= 10*1024*1024);
			~CacheNodeList();
			char* allocate(unsigned int length);
			unsigned int nodeCount();
		private:
			CacheNode *headNode_;
			CacheNode *currNode_;
			unsigned int nodeSize_;
			unsigned int nodeCount_;
		};
	}

}

#endif  

