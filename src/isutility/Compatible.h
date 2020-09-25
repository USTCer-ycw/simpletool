#ifndef ISTOOL_ISUTILITY_COMPATIABLE_H
#define ISTOOL_ISUTILITY_COMPATIABLE_H
#include <stdio.h>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <functional>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <chrono>
#include <errno.h>
#include <string.h>
#include <thread>
#include <float.h>

#pragma warning(disable:4996)

#ifdef __WINDOWS__
#include <stdlib.h>
//#define ITOA(_Value, _Buffer, _Size, _Radix) ::itoa(_Value, _Buffer, _Radix)
#define ITOA(_Value, _Buffer, _Size, _Radix) istool::isutility::itoa::itoa_right(_Value, _Buffer, _Size, _Radix)
#define SNPRINTF _snprintf_s
#define Sprintf sprintf_s
#define __builtin_expect(EXP, C)  (EXP) 
#define Thread_local __declspec(thread)
#define fileno _fileno
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#include <time.h>
#pragma comment(lib,"Ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <process.h>
#include <windows.h>
#define strcpy strcpy_s
#define ISTONE_SHUT_WR  1
#endif


#ifdef __LINUX__
#include <sys/time.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <sys/socket.h>
#include <dirent.h>
#include <pwd.h>
#include <poll.h>
#include<typeinfo>
#include<arpa/inet.h>
#include<fcntl.h>
#include<netdb.h>
#include<netinet/tcp.h>
#include<arpa/inet.h>
#include <sys/eventfd.h>
#define ITOA(_Value, _Buffer, _Size, _Radix) istool::isutility::itoa::itoa_right(_Value, _Buffer, _Size, _Radix)
#define SNPRINTF snprintf
#define ADDRESS_FAMILY sa_family_t
#define ISTONE_SHUT_WR  1
#define WSAGetLastError() errno
#endif


#define PID_T uint64_t

#ifdef __WINDOWS__   //WINDOWS
#define __FUNCTION_NAME__   __FUNCTION__  
#else          //*NIX
#define __FUNCTION_NAME__   __func__ 
#endif


#ifdef __WINDOWS__
#define STRTOK	strtok_s
#define GETPID  _getpid
#else
#define STRTOK	strtok_r
#define GETPID  getpid
#endif

#ifdef __WINDOWS__
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms)*1000)
#endif

#ifdef __WINDOWS__
#define __memory_barrier() MemoryBarrier()
#else
#define __memory_barrier() __asm__ __volatile__("" ::: "memory")
#endif


#ifndef __WINDOWS__
#define _atoi64(val)     strtoll(val, NULL, 10)
#endif


static char t_errnobuf[512];

static const char* strerror_tl(int errorno)
{
#ifdef __LINUX__
	return strerror_r(errorno, t_errnobuf, sizeof t_errnobuf);
#endif
#ifdef WIN32
	return strerror(errorno);
#endif
}

#ifdef __WINDOWS__
#include <unordered_map>
#define UNORDERED_MAP std::unordered_map
#else
#include <tr1/unordered_map>
#define UNORDERED_MAP std::tr1::unordered_map
typedef unsigned char       BYTE;
#endif

#endif
