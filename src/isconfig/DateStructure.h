//
// Created by yaochuanwang on 9/25/20.
//

#ifndef SIMPLETOOL_DATESTRUCTURE_H
#define SIMPLETOOL_DATESTRUCTURE_H

#include <vector>
#include <string>

using std::vector;
using std::string;
namespace Data
{
    enum class market{shanghai,shenzhen};
    enum class kinds{snap,order};

    struct timeAndPath
    {
        bool     fulltime;
        uint64_t begtime;
        uint64_t endtime;
        string   srcdir;
        string   dstdir;
    };

    struct marketType
    {
        vector<market> marketvec;
    };

//    template <bool fullmarket>
    struct stockType
    {
        bool fullmarket;
        stockType(uint16_t count) : stockcount(count),stockcodevec(stockcount) {}
        const uint16_t stockcount;
        vector<string> stockcodevec;
    };

//    template<>
//    struct stockType<true>
//    {
//    };

//    template <bool fullmarketkind>
    struct quoteType
    {
        bool fullmarketkind;
        quoteType(uint16_t count) : marketkindcount(count),kindvec(marketkindcount) {}
        const uint16_t marketkindcount;
        vector<kinds> kindvec;
    };

//    template <>
//    struct quoteType<true>
//    {
//    };
    struct XMLComparePathInfo
    {
        struct timeAndPath timeAndPath_;
        struct stockType stockType_;
        struct quoteType quoteType_;
        struct marketType marketType_;
    };
}

#endif //SIMPLETOOL_DATESTRUCTURE_H
