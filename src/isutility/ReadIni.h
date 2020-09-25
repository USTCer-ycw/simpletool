#ifndef ISTONE_UTILITY_READINI_H
#define ISTONE_UTILITY_READINI_H

#include <src/utility/NonCopyAble.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <memory>
#include <vector>
#include <stdlib.h>

using namespace std;

namespace istone
{
	namespace utility
	{
		class IniItem
		{
		public:
			IniItem(char *name, char *value);
			virtual ~IniItem(void);

			char *getName(void);
			char *getValue(void);
		private:
			char name_[30];
			char value_[500];

		};

		typedef std::vector< std::shared_ptr<IniItem>> IniItemVec;
		class ReadIni :public utility::NonCopyable
		{
		public:
			ReadIni(const char *iniFilename);
			virtual ~ReadIni(void);

			virtual std::string getIni(const char *name);
			virtual IniItemVec getIniVec(const char *name);

			std::string toString();
		private:
			IniItemVec items_;
			std::string  fileName_;

		};
		class is_equal
		{
		public:
			is_equal(const char* name)
			{
				memset(name_, 0, sizeof(name_));
				memcpy(name_, name, sizeof(name_));
			}

			bool operator() (std::shared_ptr<IniItem> &item) const
			{
				if (strcmp(item->getName(), name_) == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

		private:
			char name_[20];
		};
		extern ReadIni *currentIni;
	}
}
#endif