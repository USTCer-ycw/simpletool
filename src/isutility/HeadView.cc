
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "src/isutility/HeadView.h"

using namespace std;

HeadView::HeadView()
{
}

HeadView::~HeadView()
{
}

void HeadView::setHorizontalHeader(const string& type, const string& fileWrite)
{
	fstream outfile(fileWrite, ios::out);
	if (type == string("ISTONE_TBT_MD"))
	{
		vector<string> lineArray;
		outfile << "0x14,exchId,securityType,tradeDate,updateTime,__origNetTime,mdStreamType,SecurityID,TradingPhaseCode,"
			"NumTrades,TotalVolumeTraded,TotalValueTraded,PrevClosePx,TradePx,OpenPx,ClosePx,HighPx,LowPx,IOPV,NAV,"
			"TotalLongPosition,TotalBidQty,TotalOfferQty,WeightedAvgBidPx,WeightedAvgOfferPx,BidPriceLevel,OfferPriceLevel,";
		string str = "BidPx,BidNOfOrders,BidQty,Offerx,OfferNOfOrders,OfferQty";
		stringstream ss(str);
		while (getline(ss, str, ','))
		{
			lineArray.push_back(str);
		}
		for (int i = 1; i <= 10; i++)
		{
			outfile << lineArray[0] << i << ",";
		}
		for (int i = 1; i <= 10; i++)
		{
			outfile << lineArray[1] << i << ",";
		}
		for (int i = 1; i <= 10; i++)
		{
			outfile << lineArray[2] << i << ",";
		}
		for (int i = 1; i <= 10; i++)
		{
			outfile << lineArray[3] << i << ",";
		}
		for (int i = 1; i <= 10; i++)
		{
			outfile << lineArray[4] << i << ",";
		}
		for (int i = 1; i <= 9; i++)
		{
			outfile << lineArray[5] << i << ",";
		}
		outfile << "OfferQty10" << endl;
	}
	if (type == "ISTONE_TBT_TRADE")
	{
		outfile << "#0x16,exchId,securityType,tradeDate,TransactTime,__origNetTime,ChannelNo,ApplSeqNum,SecurityID,ExecType,TradeBSFlag,TradePrice,TradeQty,TradeMoney,BidApplSeqNum,OfferApplSeqNum" << endl;
	}
	if (type == "ISTONE_TBT_ENTRUST")
	{
		outfile << "0x17,exchId,securityType,tradeDate,TransactTime,__origNetTime,ChannelNo,ApplSeqNum,SecurityID,Side,OrderType,Price,OrderQty" << endl;
	}
	if (type == "ISTONE_TBT_ORDERQUEUE")
	{
		outfile << "0x08,exchId,tradeDate,SecurityID,Side,Price,OrderQty,queueQty,queue1,queue2,queue3,queue4,queue5,queue6,queue7,queue8,queue9,queue10,queue11,queue12,queue13,queue14,queue15,queue16,queue17,queue18,queue19,queue20,queue21,queue22,queue23,queue24,queue25,queue26,queue27,queue28,queue29,queue30,queue31,queue32,queue33,queue34,queue35,queue36,queue37,queue38,queue39,queue40,queue41,queue42,queue43,queue44,queue45,queue46,queue47,queue48,queue49,queue50" << endl;
	}
	if (type == "ISTONE_TBT_INDEX")
	{
		outfile << "0x18,exchId,securityType,tradeDate,SecurityID,TotalVolumeTrade,Turnover,PreCloseIndex,LastIndex,OpenIndex,CloseIndex,HighIndex,LowIndex" << endl;
	}
	outfile.close();
}
