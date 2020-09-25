#include "src/isutility/itoa.h"

using namespace istool;
using namespace istool::isutility;

/* ʵ��itoa������Դ�루����룩 */
char* itoa::itoa_left(int num, char *str, int size, int radix)
{
	/* ������ */
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum; /* �м���� */
	int i = 0, j, k;
	/* ȷ��unum��ֵ */
	if (radix == 10 && num < 0) /* ʮ���Ƹ��� */
	{
		unum = (unsigned)-num;
		str[i++] = '-';
	}
	else
		unum = (unsigned)num; /* ������� */
							  /* ���� */
	do
	{
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
	} while (unum);
	str[i] = '\0';
	/* ת�� */
	if (str[0] == '-') k = 1; /* ʮ���Ƹ��� */
	else k = 0;
	/* ��ԭ���ġ�/2����Ϊ��/2.0������֤��num��16~255֮�䣬radix����16ʱ��Ҳ�ܵõ���ȷ��� */
	char temp;
	for (j = k; j <= (i - k - 1) / 2.0; j++)
	{
		temp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = temp;
	}
	return str;
}

/*�Ҷ��루���油�ո�*/
char* itoa::rightAlign(char *str, int size, char fill)
{
	int len = strlen(str);
	char *src = str + len;
	char *dest = str + size - 1;
	while (src >= str) //�Ҷ���
	{
		*dest = *src;
		--dest;
		--src;
	}
	/*
	while (dest >= str) //�����
	{
	*dest = fill;
	--dest;
	}
	*/

	//�����
	int fillSize = dest - str + 1;
	memset(str, fill, fillSize);

	return str;
}

/* ʵ��itoa������Դ�루�Ҷ��룩 */
char* itoa::itoa_right(int num, char *str, int size, int radix)
{
	itoa_left(num, str, size, radix);
	return rightAlign(str, size);
}
