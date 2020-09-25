// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef ISTOOL_ISUTILITY_FILEUTIL_H
#define ISTOOL_ISUTILITY_FILEUTIL_H

#include <stdint.h>
#include <src/isutility/StringPiece.h>
#include <src/isutility/NonCopyAble.h>
#include <src/isutility/Compatible.h>

using namespace std;
const int MAX_LINE_LEN = 2048;

namespace istool
{
	namespace isutility
	{
		class FileReader
		{
		public:
			FileReader(string filename);
			~FileReader();
			int readFile(vector<string> &content);
			bool readLine(char *buffer);
		private:
			FILE* fp_;
			char buffer_[MAX_LINE_LEN];
		};

		// not thread safe
		class AppendFile : isutility::NonCopyable
		{
		public:
			explicit AppendFile(StringArg filename);
			~AppendFile();
			void append(const char* logline, const size_t len);
			void flush();
			size_t writtenBytes() const { return writtenBytes_; }
		private:
			size_t write(const char* logline, size_t len);
			FILE* fp_;
			char buffer_[64 * 1024];
			size_t writtenBytes_;
		};
	}

}

#endif  

