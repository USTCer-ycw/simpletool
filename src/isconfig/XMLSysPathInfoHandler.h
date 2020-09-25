
#ifndef _ISHTOOL_CONFIG_XMLSYSPATHINFOHANDLE_H_
#define _ISHTOOL_CONFIG_XMLSYSPATHINFOHANDLE_H_


#include <sstream>

#include "src/isconfig/DateStructure.h"
#include "src/istinyxml2/tinyxml2.h" 
#include "src/isutility/NonCopyAble.h"

using namespace istool;
using namespace tinyxml2;
using namespace istool::isutility;
using namespace Data;
using std::stringstream;


namespace Simpletool
{

    const int size_ = 10;
    template <int size>
    struct test
    {

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
//        void print()
//        {
//            string a;
//            std::printf("%d\n",sizeof(a));
//            std::printf("%d\n",sizeof(timeAndPath));
//            printf("%d\n",sizeof(marketType));
//            printf("%d\n",sizeof(stockType));
//            printf("%d\n",sizeof(quoteType));
//        }
        XMLComparePathInfo* GetComparePathInfo() const { return comparePathInfo_; }
    private:
        XMLComparePathInfo* comparePathInfo_;
        tinyxml2::XMLElement* root_;
        tinyxml2::XMLDocument doc_;
        bool b;
        stockType<b> stockType_;
    };
}



#endif // _ISHTOOL_CONFIG_XMLSYSPATHINFOHANDLE_H_
