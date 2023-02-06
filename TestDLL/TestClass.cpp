#include "TestClass.h"

TestClass::TestClass()
{
	Val = 10;
}

TESTDLL_API int GetVal()
{
	return 100;
}

extern TESTDLL_API int g_val = 200;