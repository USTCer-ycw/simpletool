#include <src/isutility/Logging.h>
#include <src/isutility/CurrentThread.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <exception>
#include "src/isutility/Utility.h"

using namespace istool;

namespace istool
{
	thread_local char t_time[32];
	thread_local time_t t_lastSecond;
	
	Logger::LogLevel initLogLevel()
	{
		if (::getenv("ISTONE_LOG_TRACE"))
			return Logger::TRACE;
		else if (::getenv("ISTONE_LOG_DEBUG"))
			return Logger::DEBUG;
		else
			return Logger::INFO;
	}

	Logger::LogLevel g_logLevel = initLogLevel();

	const char* LogLevelName[Logger::NUM_LOG_LEVELS] =
	{
		"TRACE  ",
		"DEBUG  ",
		"INFO   ",
		"WARN   ",
		"ERR    ",
		"THROW  ",
		"FATAL  ",
	};

	// helper class for known string length at compile time
	class T
	{
	public:
		T(const char* str, unsigned len)
			:str_(str),
			len_(len)
		{
			assert(strlen(str) == len_);
		}

		const char* str_;
		const unsigned len_;
	};

	inline LogStream& operator<<(LogStream& s, T v)
	{
		s.append(v.str_, v.len_);
		return s;
	}

	inline LogStream& operator<<(LogStream& s, const Logger::SourceFile& v)
	{
		s.append(v.data_, v.size_);
		return s;
	}

	void defaultOutput(const char* msg, int len)
	{
		size_t n = fwrite(msg, 1, len, stdout);
		//FIXME check n
		(void)n;
	}

	void defaultFlush()
	{
		fflush(stdout);
	}

	Logger::OutputFunc g_output = defaultOutput;
	Logger::FlushFunc g_flush = defaultFlush;
}

Logger::Impl::Impl(LogLevel level, int savedErrno, const SourceFile& file, int line)
	: time_(Timestamp::now()),
	stream_(),
	level_(level),
	line_(line),
	basename_(file)
{
	formatTime();
	currentthread::tid();
	stream_ << T(LogLevelName[level], 7);
	stream_ << T(currentthread::tidString(), currentthread::tidStringLength());
	stream_ << " ";
	if (savedErrno != 0)
	{
		stream_ << strerror_tl(savedErrno) << " (errno=" << savedErrno << ") ";
	}
}

void Logger::Impl::formatTime()
{
	int64_t microSecondsSinceEpoch = time_.microSecondsSinceEpoch();
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch / Timestamp::kMicroSecondsPerSecond);
	int microseconds = static_cast<int>(microSecondsSinceEpoch % Timestamp::kMicroSecondsPerSecond);
	if (seconds != t_lastSecond)
	{
		t_lastSecond = seconds;
		struct tm tm_time;


#ifdef __LINUX__
		//	::gmtime_r(&seconds, &tm_time);
		::localtime_r(&seconds, &tm_time);
#endif

#ifdef WIN32
		//	_gmtime64_s(&tm_time,&seconds);
		_localtime64_s(&tm_time, &seconds);
#endif


		int len = SNPRINTF(t_time, sizeof(t_time), "%4d%02d%02d %02d:%02d:%02d",
			tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
			tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
		assert(len == 17); (void)len;
	}
	Fmt us(".%06dZ ", microseconds);
	assert(us.length() == 9);
	stream_ << T(t_time, 17) << T(us.data(), 9) << microSecondsSinceEpoch << " ";
}

void Logger::Impl::finish()
{
	stream_ << " - " << basename_ << ':' << line_ << '\n';
}

Logger::Logger(SourceFile file, int line)
	: impl_(INFO, 0, file, line)
{
}

Logger::Logger(SourceFile file, int line, LogLevel level, const char* func)
	: impl_(level, 0, file, line)
{
	impl_.stream_ << func << ' ';
	if (impl_.level_ == THROW)
	{
		impl_.finish();
		const LogStream::Buffer& buf(stream().buffer());
		g_output(buf.data(), buf.length());
		g_flush();
		fprintf(stderr, "exception:%s\n", func);
#ifdef __WINDOWS__
		throw std::exception(func);
#else
		throw std::exception();
#endif
	}
}

Logger::Logger(SourceFile file, int line, LogLevel level)
	: impl_(level, 0, file, line)
{
}

Logger::Logger(SourceFile file, int line, bool toAbort)
	: impl_(toAbort ? FATAL : ERR, errno, file, line)
{
}

Logger::~Logger()
{
	impl_.finish();
	const LogStream::Buffer& buf(stream().buffer());
	g_output(buf.data(), buf.length());

	if (impl_.level_ == FATAL)
	{
		g_flush();
		fprintf(stderr, "fatal:%s\n", buf.data());
		//让异步程序可以写入日志
		SLEEP(2000);
		abort();
	}
}

void Logger::setLogLevel(Logger::LogLevel level)
{
	g_logLevel = level;
}

void Logger::setOutput(OutputFunc out)
{
	g_output = out;
}

Logger::OutputFunc Logger::getOutput()
{
	return g_output;
}

void Logger::setFlush(FlushFunc flush)
{
	g_flush = flush;
}

Logger::OutputFunc Logger::getDefaultOutput()
{
	return defaultOutput;
}

