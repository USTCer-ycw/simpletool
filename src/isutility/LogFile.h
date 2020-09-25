#ifndef ISTOOL_ISUTILITY_LOGFILE_H
#define ISTOOL_ISUTILITY_LOGFILE_H

#include <mutex>
#include <memory>
#include <src/isutility/NonCopyAble.h>
#include <src/isutility/Types.h>

namespace istool
{
	namespace ProcessInfo
	{
		uint64_t pid();
		string hostname();
	}
	namespace isutility
	{
		class AppendFile;

		class LogFile : isutility::NonCopyable
		{
		public:
			LogFile(const string& basename,
				size_t rollSize,
				bool threadSafe = true,
				int flushInterval = 3,
				int checkEveryN = 1024);
			~LogFile();

			void append(const char* logline, int len);
			void flush();
			bool rollFile();

		private:
			void append_unlocked(const char* logline, int len);

			static string getLogFileName(const string& basename, time_t* now);

			const string basename_;
			const size_t rollSize_;
			const int flushInterval_;
			const int checkEveryN_;

			int count_;

			std::unique_ptr<std::mutex> mutex_;
			time_t startOfPeriod_;
			time_t lastRoll_;
			time_t lastFlush_;
			std::unique_ptr<AppendFile> file_;

			const static int kRollPerSeconds_ = 60 * 60 * 24;
		};
	}
}
#endif  // ISTOOL_ISUTILITY_LOGFILE_H
