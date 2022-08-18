#pragma once
#include "Object.hpp"

template <typename T>
class object2D : public objectBase
{
public:
	//std::string name;
	Rect_<T> rect;

	Vector2D_<T> force;
	Vector2D_<T> accel;
	Vector2D_<T> velocity;
	//float mass = 0.0f;

	//OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

public:
	object2D() {};
	object2D(Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT) : rect(_rect), type(_type), mass(0.0f) {};
	~object2D() {};

public:
	void Random()
	{
		rect = Rect_<T>(20 + rand() % 80, 20 + rand() % 80, 2 + (rand() % 20), 2 + (rand() % 20));
	}

	void moveTo(Point_<T> _pos)
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Point_<T> offset = _pos - rect.LT;
			rect.offset(offset);
		}
	}

	void moveTo(int _x, int _y)
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			moveTo(Point_<T>(_x, _y));
		}
	}

	Circle_<T> getCircle()
	{
		return Circle_<T>(rect.center(), rect.length() / 2.0f);
	}

public:
	virtual void frame(float _dt) {};
};