#ifndef ISTOOL_ISUTILITY_LOGGING_H
#define ISTOOL_ISUTILITY_LOGGING_H

#include <src/isutility/LogStream.h>
#include <src/isutility/Timestamp.h>
#ifdef __WINDOWS__
#define DIRDELIMIER '\\'
#endif
#ifdef __LINUX__
#define DIRDELIMIER '/'
#endif

namespace istool
{
class Logger
{
 public:
  enum LogLevel
  {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERR,
    THROW,
    FATAL,
    NUM_LOG_LEVELS,
  };

  // compile time calculation of basename of source file
  class SourceFile
  {
   public:
    template<int N>
    inline SourceFile(const char (&arr)[N])
      : data_(arr),
        size_(N-1)
    {
			const char* slash = strrchr(data_, DIRDELIMIER); // builtin function
      if (slash)
      {
        data_ = slash + 1;
        size_ -= static_cast<int>(data_ - arr);
      }
    }

    explicit SourceFile(const char* filename)
      : data_(filename)
    {
			const char* slash = strrchr(filename, DIRDELIMIER);
      if (slash)
      {
        data_ = slash + 1;
      }
      size_ = static_cast<int>(strlen(data_));
    }

    const char* data_;
    int size_;
  };

  Logger(SourceFile file, int line);
  Logger(SourceFile file, int line, LogLevel level);
  Logger(SourceFile file, int line, LogLevel level, const char* func);
  Logger(SourceFile file, int line, bool toAbort);
  ~Logger();

  LogStream& stream() { return impl_.stream_; }

  static LogLevel logLevel();
  static void setLogLevel(LogLevel level);

  typedef void (*OutputFunc)(const char* msg, int len);
  typedef void (*FlushFunc)();
  static void setOutput(OutputFunc);
  static OutputFunc getOutput();
  static OutputFunc getDefaultOutput();
  static void setFlush(FlushFunc);

 private:

class Impl
{
 public:
  typedef Logger::LogLevel LogLevel;
  Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
  void formatTime();
  void finish();

  Timestamp time_;
  LogStream stream_;
  LogLevel level_;
  int line_;
  SourceFile basename_;
};

  Impl impl_;

};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel Logger::logLevel()
{
  return g_logLevel;
}

//
// CAUTION: do not write:
//
// if (good)
//   LOG_INFO << "Good news";
// else
//   LOG_WARN << "Bad news";
//
// this expends to
//
// if (good)
//   if (logging_INFO)
//     logInfoStream << "Good news";
//   else
//     logWarnStream << "Bad news";
//
#define LOG_TRACE if (istool::Logger::logLevel() <= istool::Logger::TRACE) \
	istool::Logger(__FILE__, __LINE__, istool::Logger::TRACE, __FUNCTION_NAME__).stream()
#define LOG_DEBUG if (istool::Logger::logLevel() <= istool::Logger::DEBUG) \
	istool::Logger(__FILE__, __LINE__, istool::Logger::DEBUG, __FUNCTION_NAME__).stream()
#define LOG_INFO if (istool::Logger::logLevel() <= istool::Logger::INFO) \
  istool::Logger(__FILE__, __LINE__).stream()
#define LOG_WARN istool::Logger(__FILE__, __LINE__, istool::Logger::WARN).stream()
#define LOG_ERROR istool::Logger(__FILE__, __LINE__, istool::Logger::ERR).stream()
#define LOG_FATAL istool::Logger(__FILE__, __LINE__, istool::Logger::FATAL).stream()
#define LOG_SYSERR istool::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL istool::Logger(__FILE__, __LINE__, true).stream()
//throw 会导致程序直接跳转到catch，清楚逻辑的情况下才慎用
#define LOG_THROW(str) istool::Logger(__FILE__, __LINE__, istool::Logger::THROW,str).stream()


// Taken from glog/logging.h
//
// Check that the input is non NULL.  This very useful in constructor
// initializer lists.

#define CHECK_NOTNULL(val) \
  ::istool::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

// A small helper for CHECK_NOTNULL().
template <typename T>
T* CheckNotNull(Logger::SourceFile file, int line, const char *names, T* ptr)
{
  if (ptr == NULL)
  {
   Logger(file, line, Logger::FATAL).stream() << names;
  }
  return ptr;
}

}

#endif  // ISTOOL_ISUTILITY_LOGGING_H
