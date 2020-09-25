#if !defined(ISTONE_UTILITY_AUTOCLEAN_HELPER_H)
#define ISTONE_UTILITY_AUTOCLEAN_HELPER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

namespace istool
{
	namespace isutility
	{
		class AutoCleanHelper
		{
		public:
			static AutoCleanHelper& instance();
			~AutoCleanHelper();
			            
		private:
			AutoCleanHelper();
			AutoCleanHelper(const AutoCleanHelper&);
			AutoCleanHelper& operator=(const AutoCleanHelper&);

			void autoClean();
			void clean();
			bool isTradingFileExist();
			void createTradingFile();
			std::string readTradingDay();
			void updateTradingDay();
			
			std::string fileName_;
			std::vector<std::string> files_;
		};
	}
}

#endif //ISTONE_UTILITY_AUTOCLEAN_HELPER_H
