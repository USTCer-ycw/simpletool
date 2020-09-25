
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

#include <iostream>

#include "src/isconfig/PathHelper.h"
#include "src/isconfig/ConfigSetting.h"


PathHelper::PathHelper()
{

}


PathHelper::~PathHelper()
{

}

std::string PathHelper::acquireBegTime() const 
{
	return begTime_;
}

std::string PathHelper::acquireEndTime() const 
{
	return endTime_;
}

std::vector<std::string> PathHelper::acquireSrcFile() const
{
	return srcFiles_;
}

std::vector<std::string> PathHelper::acquireDstFile() const
{
	return dstFiles_;
}


bool PathHelper::safeCreateDir(const std::string& path)
{
	return true;
}


bool PathHelper::acquiredFiles(const std::string& path, std::vector<std::string>& fileVec)
{
	std::cout << "path:" << path << std::endl;

	DIR* pDir = NULL;
	struct dirent* pFile = NULL;

	pDir = ::opendir(path.c_str());
	if (NULL == pDir) return false;

	while ((pFile = ::readdir(pDir)) != NULL)
	{
		// FIXME: switch
		if (::strcmp(pFile -> d_name, ".") == 0 || ::strcmp(pFile -> d_name, "..") == 0)
		{
			continue;
		}
		else if (pFile -> d_type == DT_DIR) // child directory
		{
			std::string childDir = path + "/" + pFile -> d_name;
			acquiredFiles(childDir, fileVec);
		}
		else if ((pFile -> d_type == DT_LNK) || (pFile -> d_type == DT_SOCK) || (pFile -> d_type == DT_FIFO) || (pFile -> d_type == DT_BLK))
		{
			continue;
		}
		else if (pFile -> d_type == DT_REG)
		{
			std::string fileName = pFile -> d_name;
			std::cout << "fileName:" << fileName << std::endl;
				
			fileVec.emplace_back(std::string(path + "/" + fileName));
		}
		else
		{
			std::cout << "unknow file type." << std::endl;
		}
	}
	::closedir(pDir);
	return fileVec.empty() ? false : true;
}


bool PathHelper::storeFileName()
{
	ConfigSetting::instance().initCompare();

	begTime_ = ConfigSetting::instance().begTime_;
	endTime_ = ConfigSetting::instance().endTime_;

	std::string srcDir = ConfigSetting::instance().compareSrcDir_;
	std::string dstDir = ConfigSetting::instance().compareDstDir_;
	
	acquiredFiles(srcDir, srcFiles_);
	acquiredFiles(dstDir, dstFiles_);
	
	return true;
}


