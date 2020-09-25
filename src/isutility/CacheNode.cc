#include "src/utility/CacheNode.h"

using namespace istone::utility;

CacheNode::CacheNode(unsigned int size)
{
	totalSize_ = size;
	availableSize_ = size;
	headPtr_ = reinterpret_cast<char*>(malloc(size));
	availablePtr_ = headPtr_;
	next_ = nullptr;
}


CacheNode::~CacheNode()
{
	free(headPtr_);
}


char* CacheNode::allocate(unsigned int length)
{
	if(length <= availableSize_)
	{
		availableSize_ -= length;
		char *retPtr = availablePtr_;
		availablePtr_ += length;
		return retPtr;
	}
	return nullptr;
}


void CacheNode::setNext(CacheNode* next)
{
	next_ = next;
}


CacheNode* CacheNode::getNext()
{
	return next_;
}


unsigned int CacheNode::availableSize()
{
	return availableSize_;
}
