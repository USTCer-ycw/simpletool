
#include <stdio.h>
#include <assert.h>

#include <algorithm>
#include <functional>
#include <type_traits>

#include <src/utility/ReadIni.h>
#include <src/utility/Compatible.h>


using namespace istone::utility;
using namespace std::placeholders;

IniItem::IniItem(char *name, char *value)
{
  
  assert(strlen(name) < 30 );
  assert(strlen(value) < 500 );
  memcpy(name_,name, sizeof(name_)-1);
  memcpy(value_,value, sizeof(value_)-1);
}

IniItem::~IniItem(void)
{
  //printf("1");
}

char *IniItem::getName(void)
{
	return name_;
}

char *IniItem::getValue(void)
{
	return value_;
}

ReadIni::ReadIni(const char *iniFilename)
{
	FILE *configFile;
	char *pLast=NULL;

	const int BUF_SIZE = 1024;
	char buffer[BUF_SIZE];

	configFile=fopen(iniFilename,"rt");

	if (configFile==NULL)
	{
		return;
	}

	fileName_ = iniFilename;

	while (fgets(buffer,BUF_SIZE,configFile)!=NULL)
	{
		char *name,*value;
		if (STRTOK(buffer,"\n\r",&pLast)==NULL)
			continue;
		if (buffer[0]=='#')
			continue;
		name=STRTOK(buffer,"\n\r=",&pLast);
		value=STRTOK(NULL,"\n\r",&pLast);
		if (name==NULL)
		{
			continue;
		}
		items_.push_back(std::shared_ptr<IniItem>(new  IniItem(name,value)));
	}
	fclose(configFile);
}


ReadIni::~ReadIni(void)
{
}

std::string ReadIni::getIni(const char *name)
{
	IniItemVec::iterator it = std::find_if(items_.begin(), items_.end(), is_equal(name));
	if (it != items_.end())
	{
		return (*it)->getValue();
	}
	return "";
}

IniItemVec ReadIni::getIniVec(const char *name)
{
	IniItemVec itemVec;
	auto it = std::find_if(items_.begin(), items_.end(), is_equal(name));
	while (it != items_.end())
	{
		itemVec.push_back((*it));
		items_.erase(it);
		it = std::find_if(items_.begin(), items_.end(), is_equal(name));
	}
	return itemVec;
}

std::string ReadIni::toString()
{
	std::string stringInfo;
	stringInfo += "  \nConfig file= " + fileName_;
	stringInfo += "\n===================================================";

	for (auto row : items_)
	{
		stringInfo += std::string("\n") + row->getName() + std::string(": ") + row->getValue();
	}

	stringInfo += "\n===================================================\n";
	return stringInfo;
}

