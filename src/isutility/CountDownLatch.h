// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef ISTONE_ISUTILITY_COUNTDOWNLATCH_H
#define ISTONE_ISUTILITY_COUNTDOWNLATCH_H

#include <mutex>

#include <src/isutility/Condition.h>
#include <src/isutility/NonCopyAble.h>

namespace istool
{

class CountDownLatch : isutility::NonCopyable
{
 public:

  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount() const;

 private:
  mutable MutexLock mutex_;
  Condition condition_;
  int count_;
};

}
#endif  // ISTOOL_ISUTILITY_COUNTDOWNLATCH_H
