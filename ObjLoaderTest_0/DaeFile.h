#pragma once
#include <fstream>
#include <sstream>

#include "Define.hpp"
#include "tinystr.h"
#include "tinyxml.h"

class DaeFile
{
public:
	bool Load(std::string filename);

public:
	bool SplitString(std::string line, char delimiter, std::vector<std::string>& dst);
};