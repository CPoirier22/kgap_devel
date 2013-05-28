#include "../include/kt4585app_pp_app.h"
#include "../../../include/common/include/glibc.h"

int getIntFromString(char * str)
{
	int cnt = 0;
	int result = 0;
	int mul = 1;

	while (cnt < 5 && str[cnt] != 0)
	{
		result *= mul;
		result += str[cnt]-'0';
		mul *= 10;
		cnt++;
	}
	return result;
}

