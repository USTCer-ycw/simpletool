
#ifndef _ISHTOOL_CONFIG_XMLSYSPATHINFOHANDLE_H_
#define _ISHTOOL_CONFIG_XMLSYSPATHINFOHANDLE_H_

#include <string>
#include <sstream>
#include <vector>
#include "src/istinyxml2/tinyxml2.h" 
#include "src/isutility/NonCopyAble.h"

using namespace istool;
using namespace tinyxml2;
using namespace istool::isutility;
using std::string;
using std::stringstream;
using std::vector;

namespace Simpletool
{
    struct XMLComparePathInfo
    {
        string fullTime_;
        string begTime_;
        string endTime_;
        string compareSrcDir_;
        string compareDstDir_;

        string market_;
        string isFullMarket_;
        int stockCount_;
        string stockCode_;

        string marketKind_;
        int marketKindCount_;

        string kinds;

        vector<string> kindVec;
        vector<string> stockCodeVec;
    };


    class XMLSysPathInfoHandler : public NonCopyable
    {
    public:
        XMLSysPathInfoHandler();
        ~XMLSysPathInfoHandler();

    public:
        bool LoadXMLForCompare(const char* xmlPath);
        bool LoadTimeandpath(const char* xmlPath);
        bool LoadMarketType(const char* xmlPath);
        bool LoadStockType(const char* xmlPath);
        bool LoadQuoteType(const char* xmlPath);
    public:


        XMLComparePathInfo* GetComparePathInfo() const { return comparePathInfo_; }
    private:
        XMLComparePathInfo* comparePathInfo_;
        tinyxml2::XMLElement* root_;
        tinyxml2::XMLDocument doc_;
    };
}



#endif // _ISHTOOL_CONFIG_XMLSYSPATHINFOHANDLE_H_
