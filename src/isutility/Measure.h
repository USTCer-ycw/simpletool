#ifndef ISTONE_UTILITY_MEASURE_H
#define ISTONE_UTILITY_MEASURE_H

#include <vector>
#include "src/utility/Utility.h"

using namespace std;
using namespace istone::utility;

namespace istone
{
	namespace utility
	{
		class Measure
		{
		public:
			Measure(const char* funcName, vector<uint64_t>& timeVec, bool debugLog = false,bool async = false, int index = 1000);
			~Measure();
		private:
			uint64_t startTime_;
			std::string funcName_;
			bool debugLog_;
			bool async_;
			int index_; 
			vector<uint64_t>* timeVec_;
		};
	}
}

#endif
