
#include "src/isutility/Logging.h"
#include "src/istinyxml2/tinyxml2.h" 
#include "src/isconfig/XMLSysPathInfoHandler.h"

using namespace Simpletool;

XMLSysPathInfoHandler::XMLSysPathInfoHandler()
	: comparePathInfo_(new XMLComparePathInfo())
{
}


XMLSysPathInfoHandler::~XMLSysPathInfoHandler()
{
//    Clang-Tidy: 'if' statement is unnecessary; deleting null pointer has no effect
    delete comparePathInfo_;
    comparePathInfo_ = nullptr;
}


bool XMLSysPathInfoHandler::LoadXMLForCompare(const char* xmlPath)
{
	tinyxml2::XMLError error = doc_.LoadFile(xmlPath);
	if (error != tinyxml2::XMLError::XML_SUCCESS)
	{
		LOG_ERROR << "LoadXMLForCompare error " << error;
		return false;
	}

	root_ = doc_.RootElement();
	if (root_ == nullptr)
	{
		LOG_ERROR << "LoadXMLForCompare Root not found ";
		return false;
	}
	return (LoadTimeandpath(xmlPath) && LoadMarketType(xmlPath) && LoadStockType(xmlPath) && LoadQuoteType(xmlPath));
}


bool XMLSysPathInfoHandler::LoadTimeandpath(const char *xmlPath)
{
    tinyxml2::XMLElement* sysPathNode = root_->FirstChildElement("TimeAndPath");
    if (sysPathNode != nullptr)
    {
        comparePathInfo_->fullTime_ = sysPathNode->FirstChildElement("FullTime")->GetText();

        comparePathInfo_->compareSrcDir_ = sysPathNode->FirstChildElement("SrcDir")->GetText();

        comparePathInfo_->compareDstDir_ = sysPathNode->FirstChildElement("DstDir")->GetText();

        if(comparePathInfo_->fullTime_ == "1")
        {
            comparePathInfo_->begTime_ = "any";
            comparePathInfo_->endTime_ = "any";
        }
        else
        {
            comparePathInfo_->begTime_ = sysPathNode->FirstChildElement("BegTime")->GetText();
            comparePathInfo_->endTime_ = sysPathNode->FirstChildElement("EndTime")->GetText();
        }
    }
    else
    {
        LOG_ERROR << "ComparePath node not found";
        return false;
    }
    return true;
}

bool XMLSysPathInfoHandler::LoadMarketType(const char *xmlPath)
{
    tinyxml2::XMLElement* sysPathNode = root_->FirstChildElement("MarketType");
    if (sysPathNode != nullptr)
    {
        comparePathInfo_->market_ = sysPathNode->FirstChildElement("Market")->GetText();
    }
    else
    {
        LOG_ERROR << "ComparePath node not found";
        return false;
    }
    return true;
}

bool XMLSysPathInfoHandler::LoadStockType(const char *xmlPath)
{
    tinyxml2::XMLElement* sysPathNode = root_->FirstChildElement("StockType");
    if (sysPathNode != nullptr)
    {
        comparePathInfo_->isFullMarket_ = sysPathNode->FirstChildElement("IsFullMarket")->GetText();
        if(comparePathInfo_->isFullMarket_ == "1")
        {
            comparePathInfo_->stockCount_ = 0;
        }
        else
        {
            stringstream count_ ; count_ << sysPathNode->FirstChildElement("StockCount")->GetText();
            count_ >> comparePathInfo_->stockCount_;
            comparePathInfo_->stockCode_ = sysPathNode->FirstChildElement("StockCode")->GetText();
            ssize_t size = comparePathInfo_->stockCode_.size();
            ssize_t start = 0; int i = 0;
            comparePathInfo_->stockCodeVec.resize(comparePathInfo_->stockCount_);
            while(start < size && i < comparePathInfo_->stockCount_)
            {
                ssize_t end = comparePathInfo_->stockCode_.find(",",start);
                comparePathInfo_->stockCodeVec[i++] = comparePathInfo_->stockCode_.substr(start,end-start);
                start = end + 1;
            }
        }
    }
    else
    {
        LOG_ERROR << "ComparePath node not found";
        return false;
    }
    return true;
}

bool XMLSysPathInfoHandler::LoadQuoteType(const char *xmlPath)
{
    tinyxml2::XMLElement* sysPathNode = root_->FirstChildElement("QuoteType");
    if (sysPathNode != nullptr)
    {
        comparePathInfo_->marketKind_ = sysPathNode->FirstChildElement("FullMarketKind")->GetText();
        if (comparePathInfo_->marketKind_ == "1")
        {
            comparePathInfo_->marketKindCount_ = 0;
        }
        else
        {
            stringstream count_;
            count_ << sysPathNode->FirstChildElement("MarketKindCount")->GetText();
            count_ >> comparePathInfo_->marketKindCount_;
            comparePathInfo_->kinds = sysPathNode->FirstChildElement("Kind")->GetText();
            ssize_t size = comparePathInfo_->kinds.size();
            ssize_t start = 0;
            int idx = 0;
            comparePathInfo_->kindVec.resize(comparePathInfo_->marketKindCount_);
            while (start < size && idx < comparePathInfo_->marketKindCount_)
            {
                ssize_t end = comparePathInfo_->kinds.find(",", start);
                comparePathInfo_->kindVec[idx++] = comparePathInfo_->kinds.substr(start, end - start);
                start = end + 1;
            }
        }
    }
    else
    {
        LOG_ERROR << "ComparePath node not found";
        return false;
    }
    return true;
}