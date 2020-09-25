#ifndef ISTOOL_ISUTILITY_UTILITY_H
#define ISTOOL_ISUTILITY_UTILITY_H

#ifdef WIN32
#include <io.h>
#include <direct.h>
#else	//__LINUX__
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#endif

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "src/isutility/Compatible.h"

#define PATH_DELIMITER '/'

using namespace std;
using namespace std::chrono;

#define CURR_STIME_POINT  duration_cast<chrono::seconds>(system_clock::now().time_since_epoch()).count()
#define CURR_NSTIME_POINT duration_cast<chrono::nanoseconds> (system_clock::now().time_since_epoch()).count()
#define CURR_USTIME_POINT duration_cast<chrono::microseconds>(system_clock::now().time_since_epoch()).count()
#define CURR_MSTIME_POINT duration_cast<chrono::milliseconds>(system_clock::now().time_since_epoch()).count()


#define DOUBLE_MIN_VALUE 0.000000001  //根据需要调整这个值
#define IS_DOUBLE_ZERO(d) (abs(d) < DOUBLE_MIN_VALUE) 
#define IS_DOUBLE_EQUAL(a,b) (abs((a)-(b)) < DOUBLE_MIN_VALUE) 
#define SIGN(x) int((x > 0) - (x < 0))

namespace istool
{
	namespace isutility
	{
		static const char digits[] = "9876543210123456789";
		static const char* zero = digits + 9;
		typedef std::chrono::duration<int, std::ratio<60 * 60>> HoursType;
		static std::string g_tradingDay;

		template<typename T>
		size_t convert(char buf[], T value)
		{
			T i = value;
			char* p = buf;
			do
			{
				int lsd = static_cast<int>(i % 10);
				i /= 10;
				*p++ = zero[lsd];
			} while (i != 0);

			if (value < 0)
			{
				*p++ = '-';
			}
			*p = '\0';
			std::reverse(buf, p);

			return p - buf;
		}

		static const std::string getCurrentSystemTime()
		{
			auto tt = system_clock::to_time_t(system_clock::now());
			struct tm* ptm = localtime(&tt);
			char date[9] = { 0 };
			sprintf(date, "%02d:%02d:%02d", (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
			return std::string(date);
		}

		static std::string convertToTimeString(int time)
		{
			int hour = time / 10000;
			int t = time % 10000;
			int minute = t / 100;
			t = t % 100;
			char buf[20];
			sprintf(buf, "%02d:%02d:%02d", hour, minute, t);
			return std::string(buf);
		}
		static std::vector<std::string> split(const  std::string& sourcestr, const std::string& delimiter = ",")
		{
			std::vector<std::string> elems;
			size_t pos = 0;
			size_t len = sourcestr.length();
			size_t delim_len = delimiter.length();
			if (delim_len == 0) return elems;
			while (pos < len)
			{
				int find_pos = sourcestr.find(delimiter, pos);
				if (find_pos < 0)
				{
					elems.push_back(sourcestr.substr(pos, len - pos));
					break;
				}
				elems.push_back(sourcestr.substr(pos, find_pos - pos));
				pos = find_pos + delim_len;
			}
			return elems;
		}

		static std::string getTradingDay()
		{
			if(g_tradingDay.length() !=0)
			{
				return g_tradingDay;
			}
			time_point<system_clock> tpNow = system_clock::now();
			time_point<system_clock> tpTradingDay = tpNow;
			auto ttNow = system_clock::to_time_t(tpNow);
			struct tm* ptm = localtime(&ttNow);

			if (ptm->tm_hour >= 15)
			{
				if (ptm->tm_wday != 5)
				{
					//非周五夜市，取下一天为交易日
					HoursType oneDay(24);
					tpTradingDay = tpNow + oneDay;
				}
				else
				{
					//周五下午15点之后启动，取下个周一的日期为交易日
					HoursType oneDay(24 * 3);
					tpTradingDay = tpNow + oneDay;
				}
			}
			else if (ptm->tm_wday == 6)
			{
				//周六早上，取下个周一的日期为交易日
				HoursType oneDay(24 * 2);
				tpTradingDay = tpNow + oneDay;
			}
			auto ttTradingDay = system_clock::to_time_t(tpTradingDay);
			ptm = localtime(&ttTradingDay);
			char day[11] = { 0 };
			SNPRINTF(day, sizeof(day), "%d%02d%02d", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday);
			g_tradingDay = std::string(day);
			return g_tradingDay;
		}
		//static void parseRow(std::string row,std::vector<std::string> &records)
		//{
		//	std::istringstream rowStream(row);
		//	while (rowStream)
		//	{
		//		std::string s;
		//		
		//		auto ret = !getline(rowStream, s, ',');
		//		if (ret)
		//			break;

		//		records.push_back(s);
		//		
		//		/*
		//		auto ret = !getline(rowStream, s, ',');
		//		records.push_back(s);
		//		if (strcmp(s.c_str(), "45") == 0)
		//		{
		//			int i = 0;
		//		}
		//		if (ret)
		//			break;	
		//			*/
		//	}
		//}
		static void parseRow(std::string row,std::vector<std::string> &records)
		{
			std::string delim = ",";
			size_t last = 0;
			size_t index = row.find_first_of(delim, last);
			while (index != std::string::npos)
			{
				records.push_back(row.substr(last, index - last));
				last = index + 1;
				index = row.find_first_of(delim, last);
			}
			if (index - last>0)
			{
				records.push_back(row.substr(last, index - last));
			}
		}

		static void strTrim(char* pStr)
		{
			char* pTmp = pStr;
			while (*pStr != '\0')
			{
				if (*pStr != ' ')
				{
					*pTmp++ = *pStr;
				}
				++pStr;
			}
			*pTmp = '\0';
		}

		///
		/// unix time convert standard time
		///

		static std::string unixTimeStampToStandardTime(uint64_t data)
		{
			char buffer[20];
			memset(buffer, 0, sizeof(buffer));
	
			// s
			time_t seconds = static_cast<time_t> (data);
	
			//ns -> s
			//time_t seconds = static_cast<time_t> (data / 1000000000);
			struct tm* tm = localtime(&seconds);

			// ms
			//uint64_t ms = (data / 1000000) % 1000;
	
			//sprintf(buffer, "%04d%02d%02d%02d%02d%02d%03d", tm->tm_year + 1900,
			//	tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, ms);
	
			sprintf(buffer, "%04d%02d%02d%02d%02d%02d", tm->tm_year + 1900,
				tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
			return std::string(buffer);
		}

		///
		/// format convert,for example:vale:32.60 -> 32
		///

		static std::vector<std::string> splitKeyFromText(const std::vector<std::string>& word, const std::string& substring)
		{
			std::vector<std::string> data;
			using size_type = std::string::size_type;

			if (!word.empty())
			{
				for (auto val : word)
				{
					size_type length  = val.size();
					size_type index   = val.find(substring);
					std::string value = val.substr(index + 1, length);
			
					//std::cout << value << std::endl;

					data.emplace_back(value);
				}
			}

			return data;
		}



		///
		/// remove unvalid character
		///

		static std::string Trim(std::string& data)
		{
			data.erase(0, data.find_first_not_of("\t\r\n"));
			data.erase(data.find_last_not_of("\t\r\n") + 1);
			return data;
		}


		///
		/// split feild from every row data
		///
		static void splitDataFromEveryRow(const std::string& data, std::vector<std::string>& text, const std::string& substring)
		{
			if (data.empty()) return;
			using size_type = std::string::size_type;
			size_type begin = 0;
			size_type index = 0;
			
			std::string line;

			while (begin != std::string::npos)
			{
				index = data.find(substring, begin);
				if (index != std::string::npos)
				{
					line  = data.substr(begin, index - begin);
					begin = index + substring.length();
				}
				else
				{
					line  = data.substr(begin);
					begin = index;
				}

				if (line.front() == ' ')
					line = line.substr(1, line.size());
				if (line.back() == ' ')
					line = line.substr(0, line.size() - 1);
				text.emplace_back(line);
			}
		}

		///
		/// convert function
		///
		static int stringToInt(const std::string& rhs)
		{
			std::stringstream stream;
			stream.clear();
			stream << rhs;
			int value = 0;
			stream >> value;

			return value;
		}

		static int64_t stringToInt64(const std::string& rhs)
		{
			std::stringstream stream;
			stream.clear();
			stream << rhs;
			int64_t value = 0;
			stream >> value;

			return value;
		}

		static uint64_t stringToUint64(const std::string& rhs)
		{
			std::stringstream stream;
			stream.clear();
			stream << rhs;
			uint64_t value = 0;
			stream >> value;

			return value;
		}

		static double stringToDouble(const std::string& rhs)
		{
			std::stringstream stream;
			stream.clear();
			stream << rhs;
			double value = 0.0;
			stream >> value;

			return value;
		}


		static bool isDigit(const std::string& rhs)
		{
			std::stringstream stream;
			stream.clear();
			stream << rhs;
			
			char   cvalue;
			int    ivalue = 0;
			double dvalue = 0.0;

			if (stream >> cvalue) 
			{
				return false;
			}
			if (!(stream >> ivalue)) 
			{
				return false;
			}

			if (!(stream >> dvalue))
			{
				return false;
			}

			return true;
		}



		///
		/// string acquired decimal point
		///
		static std::string stringGetDecimalPoint(const std::string& s, int index)
		{
			std::stringstream stream;
			// set decimal point
			stream.setf(std::ios::fixed);
			stream << std::setiosflags(std::ios::fixed | std::ios::showpoint | std::ios::right);
			stream << std::setprecision(index) << s;
			return stream.str();
		}


		// acquired current time
		static std::string stringToTime()
		{
			time_t value;
			::time(&value);
			char bufTime[64];
			::strftime(bufTime, sizeof(bufTime), "%Y-%m-%d %H:%M:%S", localtime(&value));
			return std::string(bufTime);
		}

		static void stringToTime(const std::string& info)
		{
			time_t value;
			::time(&value);
			char bufTime[64];
			::strftime(bufTime, sizeof(bufTime), "%Y-%m-%d %H:%M:%S", localtime(&value));
			std::cout << info << ":" << std::string(bufTime) << "." << std::endl;
		}

		static bool getFilePath(const std::string folder)
		{
			std::string folder_builder;
			std::string sub;
			sub.reserve(folder.size());
			for (auto it = folder.begin(); it != folder.end(); ++it)
			{
				//cout << *(folder.end()-1) << endl;  
				const char c = *it;
				sub.push_back(c);
				if (c == PATH_DELIMITER || it == folder.end() - 1)
				{
					folder_builder.append(sub);
					if (0 != ::access(folder_builder.c_str(), 0))
					{
						// this folder not exist  
						#ifdef WIN32
						if (0 != ::mkdir(folder_builder.c_str()))
						#else	//__LINUX__
						if (0 != ::mkdir(folder_builder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
						#endif
						{
							// create failed  
							return false;
						}
					}
					sub.clear();
				}
			}
			return true;
		}

		static string parseAddPort(char* addrPort, int& port)
		{
			string strAddrPort(addrPort);
			char addr[50];
			int startPos = strAddrPort.find("//", 0);
			if (startPos != std::string::npos)
			{
				int endPos = strAddrPort.find(":", startPos);
				if (endPos != std::string::npos)
				{
					string strAddr = strAddrPort.substr(startPos + 2, (endPos - startPos - 2));
					string strPort = strAddrPort.substr(endPos + 1, (strAddrPort.length() - endPos - 1));

					memset(addr, 0, sizeof(addr));
					memcpy(addr, strAddr.c_str(), strAddr.length());
					port = atoi(strPort.c_str());
				}
			}
			return string(addr);
		}

	}
}

#endif
