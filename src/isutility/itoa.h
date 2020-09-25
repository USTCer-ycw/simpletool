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
			/* ʵ��itoa������Դ�루����룩 */
			static char *itoa_left(int num, char *str, int size, int radix);

			/*�Ҷ��루���油�ո�*/
			static char *rightAlign(char *str, int size, char fill = '0');

			/* ʵ��itoa������Դ�루�Ҷ��룩 */
			static char *itoa_right(int num, char *str, int size, int radix);
		};
	}
}

#endif
