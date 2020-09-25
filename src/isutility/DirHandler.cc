
#include <fstream>
#include <iostream>
#include "src/isutility/Logging.h"
#include "src/isutility/DirHandler.h"

#ifdef __LINUX__
#include <sys/io.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h> 
#else
#include <io.h>
#include <direct.h> 
#endif 

using namespace std;
using namespace istool::isutility;

DirHandler::DirHandler()
{
}


DirHandler::~DirHandler()
{
}


DirHandler& DirHandler::instance()
{
	static DirHandler instance;
	return instance;
}


void DirHandler::mkMutiDir(const string& path)
{
#ifdef __LINUX__
	uint32_t begPath = 0;
	uint32_t endPath = 0;

	std::string fullPath = "";

	LOG_INFO << "path = " << path.c_str();

	if (DIRDELIMIER != path[0])
	{  
		fullPath = getcwd(nullptr, 0);
		begPath = fullPath.size();
		LOG_INFO << "current Path: " << fullPath.c_str();
		fullPath = fullPath + "/" + path;
	}
	else
	{
		fullPath = path;
		begPath = 1;
	}

	if (fullPath[fullPath.size() - 1] !=DIRDELIMIER)
	{
		fullPath += "/";
	}
	endPath = fullPath.size();

	//create dirs;
	for (uint32_t i = begPath; i < endPath; ++i)
	{
		if (DIRDELIMIER == fullPath[i])
		{
			std::string curPath = fullPath.substr(0, i);
			if (access(curPath.c_str(), F_OK) != 0)
			{
				if (mkdir(curPath.c_str(), S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH | S_IXUSR | S_IXGRP | S_IXOTH) == -1)
				{
					LOG_ERROR << "mkdir " << curPath.c_str() << " failed " << strerror(errno);
					return;
				}
			}
		}
	}
#else	
	int m = 0, n;
	string str1, str2;
	str1 = path;
	str2 = str1.substr(0, 2);
	str1 = str1.substr(3, str1.size());

	while (m >= 0)
	{
		m = str1.find(DIRDELIMIER);
		str2 += DIRDELIMIER + str1.substr(0, m);
		n = _access(str2.c_str(), 0); //判断该目录是否存在
		if (n == -1)
		{
			_mkdir(str2.c_str());     //创建目录
		}
		str1 = str1.substr(m + 1, str1.size());
	}
#endif
}


void DirHandler::getFiles(const string& tradingDay, const string& path, vector<string>& files)
{
#ifdef __LINUX__
	DIR* pDir = NULL;
	struct dirent* pFile = NULL;

	pDir = opendir(path.c_str());
	if (pDir == NULL) return;

	while (!(pFile = readdir(pDir))) 
	{
		if (pFile->d_type & DT_DIR) 
		{
			continue;
		}
		else 
		{
			string fileName = pFile->d_name;
			if (fileName.find(".log") != string::npos && fileName.find(tradingDay) != string::npos)
			{
				string fullPath = path + fileName;
				files.push_back(fullPath);
				LOG_INFO << "path: " << path << ", fileName: " << pFile->d_name;
			}
		}
	}
	closedir(pDir);
#else
	intptr_t hFile = 0;
	struct _finddatai64_t fileinfo;
	if ((hFile = _findfirsti64(p.assign(path).append("\\*").append(tradingDay).append("*.log").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					string temp;
					getFiles(tradingDay, temp.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnexti64(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	else
	{
		LOG_INFO << "Dir incorrect, please check dir.";
	}
#endif
}



