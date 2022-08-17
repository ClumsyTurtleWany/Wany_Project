#pragma once
#include "Rect.hpp"
#include "Circle.hpp"

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

public:
	object() {};
	object(Rect _rect, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT) : rect(_rect), type(_type) {};
	~object() {};

	void Random()
	{
		rect = Rect(20 + rand() % 80, 20 + rand() % 80, 2 + (rand() % 20), 2 + (rand() % 20));
	}

	void moveTo(Point _pos)
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Point offset = _pos - rect.LT;
			rect.offset(offset);
		}
	}

	Circle getCircle()
	{
		return Circle(rect.center(), rect.length() / 2.0f);
	}
};