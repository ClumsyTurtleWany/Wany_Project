#pragma once

#include <iostream>
#include <string>
#include <fstream>

class FileMgr
{
private:
public:
	bool load(std::string _FileName);
	bool save(std::string _FileName);
};