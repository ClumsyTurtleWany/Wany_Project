#pragma once
#include "framework.h"

class TESTDLL_API TestClass
{
public:
	int Val = 0;

public:
	TestClass();
};

TESTDLL_API int GetVal();
TESTDLL_API int g_val;