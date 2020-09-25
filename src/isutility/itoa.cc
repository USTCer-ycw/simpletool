#include "src/isutility/itoa.h"

using namespace istool;
using namespace istool::isutility;

/* 实现itoa函数的源码（左对齐） */
char* itoa::itoa_left(int num, char *str, int size, int radix)
{
	/* 索引表 */
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum; /* 中间变量 */
	int i = 0, j, k;
	/* 确定unum的值 */
	if (radix == 10 && num < 0) /* 十进制负数 */
	{
		unum = (unsigned)-num;
		str[i++] = '-';
	}
	else
		unum = (unsigned)num; /* 其它情况 */
							  /* 逆序 */
	do
	{
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
	} while (unum);
	str[i] = '\0';
	/* 转换 */
	if (str[0] == '-') k = 1; /* 十进制负数 */
	else k = 0;
	/* 将原来的“/2”改为“/2.0”，保证当num在16~255之间，radix等于16时，也能得到正确结果 */
	char temp;
	for (j = k; j <= (i - k - 1) / 2.0; j++)
	{
		temp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = temp;
	}
	return str;
}

/*右对齐（左面补空格）*/
char* itoa::rightAlign(char *str, int size, char fill)
{
	int len = strlen(str);
	char *src = str + len;
	char *dest = str + size - 1;
	while (src >= str) //右对齐
	{
		*dest = *src;
		--dest;
		--src;
	}
	/*
	while (dest >= str) //左填充
	{
	*dest = fill;
	--dest;
	}
	*/

	//左填充
	int fillSize = dest - str + 1;
	memset(str, fill, fillSize);

	return str;
}

/* 实现itoa函数的源码（右对齐） */
char* itoa::itoa_right(int num, char *str, int size, int radix)
{
	itoa_left(num, str, size, radix);
	return rightAlign(str, size);
}
