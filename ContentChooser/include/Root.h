#pragma once
#include "MySQLBank.h"

DLL_EXPORT int __stdcall factorial(int a)
{
	if (a != 1)
		return a * factorial(a - 1);
	else
		return 1;
}
