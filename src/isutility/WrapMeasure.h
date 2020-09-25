#pragma once

#include <iostream>

class WrapMeasure
{
	public:
		~WrapMeasure();

		static WrapMeasure& instance();

		int getMeasureCount();
		bool add(int row, int colume);
		void init(int row, int colume,std::string fileName);

	protected:
		WrapMeasure();

	private:
		long long sendTimePoint;
		long long recvTimePoint;

		//int msgNumber ;
		int measureCount;

};
