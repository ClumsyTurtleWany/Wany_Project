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

template <typename T>
class object
{
public:
	std::string name;
	Rect_<T> rect;
	Circle_<T> circle;

	Vector2D_<T> force;
	Vector2D_<T> accel;
	Vector2D_<T> velocity;
	float mass = 0.0f;

	OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

public:
	object() {};
	object(Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT) : rect(_rect), circle(_rect), type(_type), mass(0.0f) {};
	~object() {};

public:
	void Random()
	{
		rect = Rect_<T>(20 + rand() % 80, 20 + rand() % 80, 2 + (rand() % 20), 2 + (rand() % 20));
		circle = Circle_<T>(rect);
	}

	void moveTo(Point_<T> _pos)
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Point_<T> offset = _pos - rect.LT;
			rect.offset(offset);
			circle = Circle_<T>(rect);
		}
	}

	void moveTo(int _x, int _y)
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			moveTo(Point_<T>(_x, _y));
		}
	}

public:
	virtual void frame(float _dt) {};
};