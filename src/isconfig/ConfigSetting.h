
#ifndef ISHTOOL_ISCONFIG_CONFIGSETTING_H_
#define ISHTOOL_ISCONFIG_CONFIGSETTING_H_

#include <string>

using namespace std;

class ConfigSetting
{
	public:
		static ConfigSetting& instance();
		~ConfigSetting();

		void initCompare();
		void initLogger(const string& logFile);
		void initCompareConfig(const string& iniFilename);

	public:

		string begTime_;
		string endTime_;

		string compareSrcDir_;
		string compareDstDir_;

	private:

		int logLevel_;

		ConfigSetting();
		ConfigSetting(const ConfigSetting&);
		ConfigSetting& operator=(const ConfigSetting&);

		void operator!=(const ConfigSetting&);
		void operator==(const ConfigSetting&);
};

#endif  // ISHTOOL_ISCONFIG_CONFIGSETTING_H_

