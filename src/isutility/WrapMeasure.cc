
#include "src/ISUtility/Utility.h"
#include "src/ISUtility/Measure.h"
#include "src/ISUtility/WrapMeasure.h"

using namespace istone::utility;

WrapMeasure::WrapMeasure()
	: sendTimePoint(0)
	, recvTimePoint(0)
	//, msgNumber(0)
	, measureCount(10000)
{

}

WrapMeasure::~WrapMeasure()
{

}

void WrapMeasure::init(int row, int colume, string fileName)
{
	measureCount = row;
	g_measure = new Measure(row, colume, fileName.c_str());
}

int WrapMeasure::getMeasureCount()
{
	return measureCount;
}

WrapMeasure& WrapMeasure::instance()
{
	static WrapMeasure instance;
	return instance;
}

bool WrapMeasure::add(int row, int colume)
{
	sendTimePoint = CURR_USTIME_POINT;
	g_measure->add(row, colume, sendTimePoint);

	return true;
}




