
#include "src/isutility/Logging.h"
#include "src/isutility/Utility.h"
#include "src/isutility/FileUtil.h"
#include "src/isutility/AsyncLogging.h"
#include "src/isconfig/ConfigSetting.h"
#include "src/isconfig/XMLSysPathInfoHandler.h"

using namespace istool;
using namespace istool::isutility;
using namespace Simpletool;

AsyncLogging* g_asyncLog = NULL;
void asyncOutput(const char* msg, int len)
{
	g_asyncLog->append(msg, len);
}


ConfigSetting& ConfigSetting::instance()
{
	static ConfigSetting instance;
	return instance;
}


ConfigSetting::ConfigSetting()
{
	logLevel_ = 0;
}


ConfigSetting::~ConfigSetting()
{
	delete g_asyncLog;
	g_asyncLog = nullptr;
}


void ConfigSetting::initCompare()
{
	initLogger("./log/ishtool");
#ifdef __LINUX__
	std::string xmlPath = "./config/ComparePath.xml";

#else
	std::string xmlPath = ".\\config\\ComparePath.xml";
#endif
	initCompareConfig(xmlPath);
}


void ConfigSetting::initCompareConfig(const string& path)
{
	XMLSysPathInfoHandler* sysPathInfo = new XMLSysPathInfoHandler();
//	sysPathInfo->print();
	bool ret = sysPathInfo -> LoadXMLForCompare(path.c_str());
	if (!ret)
	{
		LOG_ERROR << "XMLComparePathInfoHandler Error";
		return;
	}

	begTime_ = sysPathInfo -> GetComparePathInfo() -> begTime_;
	endTime_ = sysPathInfo -> GetComparePathInfo() -> endTime_;
	compareSrcDir_ = sysPathInfo -> GetComparePathInfo() -> compareSrcDir_;
	compareDstDir_ = sysPathInfo -> GetComparePathInfo() -> compareDstDir_;

	delete sysPathInfo;
}


void ConfigSetting::initLogger(const string& logFile)
{
	getFilePath("./log");
	g_asyncLog = new AsyncLogging(logFile, 250 * 1000 * 1000);

	Logger::setOutput(asyncOutput);
	Logger::setLogLevel(Logger::LogLevel(logLevel_));

	g_asyncLog -> start(); 
}

