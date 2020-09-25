
#include"src/utility/Measure.h"

#include<memory>
#include<vector>
#include<string.h>
#include "src/utility/Logging.h"

Measure::Measure(const char* funcName, vector<uint64_t>& timeVec, bool debugLog, bool async,int index)
	:funcName_(funcName),debugLog_(debugLog)
{
	startTime_ = CURR_NSTIME_POINT;
	async_ = async;
	index_ = index;
	timeVec_ = &timeVec;
}
Measure::~Measure()
{
	auto endTime = CURR_NSTIME_POINT;

	if (async_)
	{
		timeVec_->push_back(endTime - startTime_);

		if (timeVec_->size() >= index_)
		{
			uint64_t totalTime = 0;
			for (int i = 0; i < timeVec_->size(); i++)
			{
				totalTime += (*timeVec_)[i];
				LOG_INFO << funcName_ << "Async.MeasureData.latency";

				if (debugLog_)
				{
					LOG_DEBUG << funcName_ << " exit.MeasureData.latency:" << (*timeVec_)[i];
				}
				else
				{
					LOG_INFO << funcName_ << " exit.MeasureData.latency:" << (*timeVec_)[i];
				}
			}
			uint64_t avgCostTime = totalTime/ timeVec_->size();
			LOG_INFO << funcName_ << "Async.Avglatency"<<avgCostTime;
			timeVec_->clear();
		}
	}
	else
	{
		if (debugLog_)
		{
			LOG_DEBUG << funcName_ << " exit.MeasureData.latency:" << endTime - startTime_;
		}
		else
		{
			LOG_INFO << funcName_ << " exit.MeasureData.latency:" << endTime - startTime_;
		}
	}
	
}
