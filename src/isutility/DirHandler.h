
#ifndef ISTOOL_ISCLEANMD_DIRHANDLER_H_
#define ISTOOL_ISCLEANMD_DIRHANDLER_H_


#include <string>
#include <vector>

using namespace std;

class DirHandler
{
	public:
		static DirHandler& instance();
		~DirHandler();
		void mkMutiDir(const string& path);
		void getFiles(const string& tradingDay, const string& path, vector<string>& files);
	private:
		DirHandler(const DirHandler&);
		DirHandler& operator=(const DirHandler&);
};

#endif // ISTOOL_ISCLEANMD_DIRHANDLER_H_ 
