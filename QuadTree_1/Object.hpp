#pragma once
#include "Rect.hpp"
#include "Vector.hpp"
#include "Circle.hpp"
#include <string>

enum class OBJECT_TYPE
{
	STATIC_OBJECT,
	DYNAMIC_OBJECT
};

class object
{
public:
	std::string name;
	Rect rect;
	Circle circle;

	Vector direction;

	OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

public:
	object() {};
	object(Rect _rect, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT) : rect(_rect), circle(_rect), type(_type) {};
	~object() {};

public:
	void Random()
	{
		rect = Rect(20 + rand() % 80, 20 + rand() % 80, 2 + (rand() % 20), 2 + (rand() % 20));
		circle = Circle(rect);
	}

	void moveTo(Point _pos)
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Point offset = _pos - rect.LT;
			rect.offset(offset);
			circle = Circle(rect);
		}
	}

	void moveTo(int _x, int _y)
	{
		moveTo(Point(_x, _y));
	}

	void move()
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			rect.offset(direction.x, direction.y);
			circle = Circle(rect);
		}
	}
};