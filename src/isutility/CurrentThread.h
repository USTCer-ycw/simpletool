// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef ISTOOL_ISUTILITY_CURRENTTHREAD_H
#define ISTOOL_ISUTILITY_CURRENTTHREAD_H

#include <stdint.h>
#include <src/isutility/Compatible.h>

namespace istool
{
	namespace currentthread
	{
		// internal
		extern thread_local uint64_t t_cachedTid;
		extern thread_local char t_tidString[32];
		extern thread_local int t_tidStringLength;
		extern thread_local const char* t_threadName;
		void cacheTid();

		inline uint64_t tid()
		{
			if (__builtin_expect(t_cachedTid == 0, 0))
			{
				cacheTid();
			}
			return t_cachedTid;
		}

		inline const char* tidString() // for logging
		{
			return t_tidString;
		}

		inline int tidStringLength() // for logging
		{
			return t_tidStringLength;
		}

		inline const char* name()
		{
			return t_threadName;
		}

		bool isMainThread();

		void sleepUsec(int64_t usec);
	}
}

#endif
