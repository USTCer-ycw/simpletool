

#include <iostream>
#include "src/isconfig/ConfigSetting.h"
int main(int argc, char *argv[])
{
    ConfigSetting::instance().initCompareConfig("");
	return 0;
}
