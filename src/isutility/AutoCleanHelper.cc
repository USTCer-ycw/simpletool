#include <stdio.h>
#ifdef __WINDOWS__
#include <io.h>
#endif
#include "src/isutility/Utility.h"
#include "src/isutility/AutoCleanHelper.h"

using namespace std;
using namespace istool;
using namespace istool::isutility;


AutoCleanHelper& AutoCleanHelper::instance()
{
	static AutoCleanHelper helper;
	return helper;
}

AutoCleanHelper::AutoCleanHelper()
:fileName_("./data/TradingDay")
{
	getFilePath("./data");
    files_.push_back("./data/Transaction.flow");

    autoClean();
}

AutoCleanHelper::~AutoCleanHelper()
{

}

void AutoCleanHelper::autoClean()
{
	if (!isTradingFileExist()) { //文件不存在
		createTradingFile();
		updateTradingDay();
		clean();
	}
	else { //文件存在
		string fromFile = readTradingDay();
		if (fromFile != isutility::getTradingDay()) { //当前为新的交易日
			updateTradingDay();
			clean();
		}
	}
}

void AutoCleanHelper::clean()
{
    for (auto row : files_) {
		remove(row.c_str());
    }
}

bool AutoCleanHelper::isTradingFileExist()
{
	if (0 != access(fileName_.c_str(), 0)) { //文件不存在
		return false;
	}
	
	return true;
}

void AutoCleanHelper::createTradingFile()
{
	FILE* fd = fopen(fileName_.c_str(), "wb+"); //创建文件
	fclose(fd);
}

string AutoCleanHelper::readTradingDay()
{
    char tradingDay[9] = {0};
    FILE* fd = fopen(fileName_.c_str(), "rb+");
    fseek(fd, 0L, SEEK_SET);
	size_t nLen = fread(&tradingDay[0], sizeof(tradingDay)-1, 1, fd);
	if (1 != nLen) {
		fclose(fd);
		return "";
	}

    fclose(fd);
    return tradingDay;
}

void AutoCleanHelper::updateTradingDay()
{
    FILE* fd = fopen(fileName_.c_str(), "rb+");
	fseek(fd, 0L, SEEK_SET);
	string tradingDay = isutility::getTradingDay();
	size_t nLen = fwrite(tradingDay.c_str(), tradingDay.length(), 1, fd);
    fclose(fd);
}

