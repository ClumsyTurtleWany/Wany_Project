#pragma once
#include "Define.hpp"
#include "tinystr.h"
#include "tinyxml.h"

class DaeFile
{
public:
	bool Load(std::string filename);
};