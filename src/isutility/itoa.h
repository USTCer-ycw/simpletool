#ifndef ISTOOL_ISUTILITY_ITOA_H
#define ISTOOL_ISUTILITY_ITOA_H

#include <string.h>


namespace istool
{
	namespace isutility
	{
		class itoa
		{
		public:
			/* 实现itoa函数的源码（左对齐） */
			static char *itoa_left(int num, char *str, int size, int radix);

			/*右对齐（左面补空格）*/
			static char *rightAlign(char *str, int size, char fill = '0');

			/* 实现itoa函数的源码（右对齐） */
			static char *itoa_right(int num, char *str, int size, int radix);
		};
	}
}

#endif
