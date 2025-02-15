#include <inttypes.h>
#include <assert.h>
#include <stdio.h>
#include <chrono>
#include <src/isutility/Timestamp.h>
#include <src/isutility/Compatible.h>

//处理64int的兼容性问题
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif



using namespace istool;

static_assert(sizeof(Timestamp) == sizeof(int64_t),"Timestamp not int64_t");

string Timestamp::toString() const
{

  char buf[32] = {0};
  int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
  int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
  SNPRINTF(buf, sizeof(buf)-1, "%lld.%06lld", seconds, microseconds);
  return buf;
}

string Timestamp::toFormattedString(bool showMicroseconds) const
{
  char buf[32] = {0};
  time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);

	struct tm tm_time;
#ifdef __LINUX__
  localtime_r(&seconds,&tm_time);
#endif

#ifdef WIN32
//	_gmtime64_s(&tm_time, &seconds);
  _localtime64_s(&tm_time, &seconds);
#endif
 

  if (showMicroseconds)
  {
    int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
    SNPRINTF(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
			tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
			tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
        microseconds);
  }
  else
  {
    SNPRINTF(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
			tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
			tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
  }
  return buf;
}

string Timestamp::dateToString() const
{
	char buf[32] = { 0 };
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);

	struct tm tm_time;
#ifdef __LINUX__
	localtime_r(&seconds, &tm_time);
#endif

#ifdef WIN32
	//	_gmtime64_s(&tm_time, &seconds);
	_localtime64_s(&tm_time, &seconds);
#endif

	int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
	SNPRINTF(buf, sizeof(buf), "%4d%02d%02d",
		tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday);
	
	return buf;
}

string Timestamp::secondToString() const
{
	char buf[32] = { 0 };
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);

	struct tm tm_time;
#ifdef __LINUX__
	localtime_r(&seconds, &tm_time);
#endif

#ifdef WIN32
	//	_gmtime64_s(&tm_time, &seconds);
	_localtime64_s(&tm_time, &seconds);
#endif

	int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
	SNPRINTF(buf, sizeof(buf), "%2d:%02d:%02d",
		tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);

	return buf;
}

Timestamp Timestamp::now()
{
	int64_t microSecondsSinceEpoch = 0;
#ifdef __LINUX__
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t seconds = tv.tv_sec;
	microSecondsSinceEpoch = seconds * kMicroSecondsPerSecond + tv.tv_usec;
#endif

#ifdef WIN32
	std::chrono::time_point<std::chrono::system_clock>p2;
	p2 = std::chrono::system_clock::now();
	microSecondsSinceEpoch = std::chrono::duration_cast<std::chrono::microseconds>(p2.time_since_epoch()).count();
#endif


	return Timestamp(microSecondsSinceEpoch);
}

