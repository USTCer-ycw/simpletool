
#ifndef ISTOOL_ISCLEANMD_HEADVIEW_H_
#define ISTOOL_ISCLEANMD_HEADVIEW_H_

#include <string>

class HeadView
{
	public:
		HeadView();
		~HeadView();
		void setHorizontalHeader(const std::string& type, const std::string& fileWrite);
};


#endif // ISTOOL_ISCLEANMD_HEADVIEW_H_
