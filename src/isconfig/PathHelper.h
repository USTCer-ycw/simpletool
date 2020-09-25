
#ifndef HTOOL_ISMDTOOL_PATHHELPER_H_
#define HTOOL_ISMDTOOL_PATHHELPER_H_

#include <vector>
#include <string>

#include "src/isutility/NonCopyAble.h"

using namespace istool;
using namespace istool::isutility;


class PathHelper : public NonCopyable
{	
	public:
		PathHelper();
		~PathHelper();
		
		std::string acquireBegTime() const;
		std::string acquireEndTime() const;
		std::vector<std::string> acquireSrcFile() const;
		std::vector<std::string> acquireDstFile() const;

		bool safeCreateDir(const std::string& path);
		bool acquiredFiles(const std::string& path, std::vector<std::string>& fileVec);
		bool storeFileName();

	private:
		
		std::string begTime_;
		std::string endTime_;

		std::vector<std::string> srcFiles_;
		std::vector<std::string> dstFiles_;
};




#endif  // HTOOL_ISMDTOOL_PATHHELPER_H_
