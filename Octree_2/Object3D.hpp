#pragma once
#include "Object.hpp"

template <typename T>
class object3D : public objectBase
{
public:
	//std::string name;
	Box_<T> box;

	Vector3D_<T> force;
	Vector3D_<T> accel;
	Vector3D_<T> velocity;
	//float mass = 0.0f;

	//OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

public:
	object3D() {};
	object3D(Box_<T> _box, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT) : box(_box), type(_type), mass(0.0f) {};
	~object3D() {};

public:
	void Random()
	{
		box = Box_<T>(Point3D_<T>(20 + rand() % 80, 20 + rand() % 80, 20 + rand() % 80), 2 + (rand() % 20), 2 + (rand() % 20), 2 + (rand() % 20));
	}

	void moveTo(Point3D_<T> _pos)
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Point3D_<T> offset = _pos - box.pos;
			box.offset(offset);
		}
	}

	void moveTo(int _x, int _y, int _z)
	{
		if (type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			moveTo(Point3D_<T>(_x, _y, _z));
		}
	}

	Sphere_<T> getSphere()
	{		
		return Sphere_<T>(box.center(), box.length() / 2.0f);
	}

public:
	virtual void frame(float _dt) {};
};

using Object = object3D<float>;