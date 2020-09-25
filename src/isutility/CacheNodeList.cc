
#include "src/utility/CacheNodeList.h"

using namespace istone::utility;

CacheNodeList::CacheNodeList(unsigned int nodeSize)
{
	nodeSize_ = nodeSize;
	headNode_ = new CacheNode(nodeSize);
	currNode_ = headNode_;
	nodeCount_ = 1;
}


CacheNodeList::~CacheNodeList()
{
	while(headNode_->getNext())
	{
		auto temp = headNode_;
		headNode_ = headNode_->getNext();
		delete temp;
	}
	delete headNode_;
}


char* CacheNodeList::allocate(unsigned int length)
{
	if (length > currNode_->availableSize())
	{
		nodeCount_++;
		auto newNode = new CacheNode(nodeSize_);
		currNode_->setNext(newNode);
		currNode_ = currNode_->getNext();
	}
	return currNode_->allocate(length);
}


unsigned int CacheNodeList::nodeCount()
{
	return nodeCount_;
}

