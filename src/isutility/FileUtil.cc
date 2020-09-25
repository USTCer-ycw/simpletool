// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include <src/isutility/FileUtil.h>
#include <src/isutility/Logging.h> // strerror_tl
#include <src/isutility/Compatible.h>
#include <src/isutility/Types.h>
#include <type_traits>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>

using namespace std;
using namespace istool;
using namespace istool::isutility;
FileReader::FileReader(string filename)
{
	fp_ = fopen(filename.c_str(), "a+");
}

FileReader::~FileReader()
{
	if (fp_)
		::fclose(fp_);
}
bool FileReader::readLine(char *buffer)
{
	int ret = 0;
	if (!fp_)
	{
		return false;
	}
	char *readResult = ::fgets(buffer, MAX_LINE_LEN, fp_);
	if(!readResult || strlen(readResult) == 0)
	{
		return false;
	}
	return true;
}
int FileReader::readFile(vector<string> &content)
{
	int ret = 0;
	if (!fp_)
	{
		return -1;
	}
	char *readResult = nullptr;
	do
	{
		readResult = ::fgets(buffer_, MAX_LINE_LEN, fp_);
		if (readResult)
		{
			string row(buffer_);
			if (row.find_first_of("#") == 0)
			{
				continue;
			}
			row.erase(row.find_last_not_of("\n") + 1);
			row.erase(row.find_last_not_of("\r") + 1);
			if (row.length() == 0)
			{
				continue;
			}
			content.push_back(row);
		}
		else
		{
			ret = -1;
			break;
		}
	} while (readResult);
	return ret;
}

AppendFile::AppendFile(StringArg filename)
  : fp_(::fopen(filename.c_str(), "a")),  // 'e' for O_CLOEXEC 'e' windows not mode 
    writtenBytes_(0)
{
  assert(fp_);
#ifdef __LINUX__
  ::setbuffer(fp_, buffer_, sizeof buffer_);
#endif
  // posix_fadvise POSIX_FADV_DONTNEED ?
}

AppendFile::~AppendFile()
{
  ::fclose(fp_);
}

void AppendFile::append(const char* logline, const size_t len)
{
  size_t n = write(logline, len);
  size_t remain = len - n;
  while (remain > 0)
  {
    size_t x = write(logline + n, remain);
    if (x == 0)
    {
      int err = ferror(fp_);
      if (err)
      {
        fprintf(stderr, "AppendFile::append() failed %s\n", strerror_tl(err));
      }
      break;
    }
    n += x;
    remain = len - n; // remain -= x
  }

  writtenBytes_ += len;
}

void AppendFile::flush()
{
  ::fflush(fp_);
}

size_t AppendFile::write(const char* line, size_t len)
{
  // #undef fwrite_unlocked
#ifdef __LINUX__
  return ::fwrite_unlocked(line, 1, len, fp_); // not thread safe
#endif

#ifdef WIN32
	return ::fwrite(line, 1, len, fp_);
#endif
}
