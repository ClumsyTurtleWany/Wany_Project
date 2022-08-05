#pragma once
#include "Rect.hpp"

enum class OBJECT_TYPE
{
	STATIC_OBJECT,
	DYNAMIC_OBJECT
};

class object
{
public:
	Rect rect;
	OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

	void Random()
	{
		rect = Rect(rand() % 100, rand() % 100, 2 + (rand() % 10), 2 + (rand() % 10));
	}
};