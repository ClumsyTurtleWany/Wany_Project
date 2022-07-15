#include "FileMgr.h"

bool FileMgr::load(std::string _FileName)
{
	std::ifstream readFile;
	readFile.open(_FileName);
	
	if (readFile.is_open())
	{


		return true;
	}
	else
	{
		return false;
	}
}

bool FileMgr::save(std::string _FileName)
{
	return false;
}
