#pragma once
#include "Object.hpp"

template <class ObjectDimension>
class Player
{
protected: 
	ObjectDimension* obj = nullptr;

public:
	virtual void frame(float _dt) = 0;
};

class Player2D : public Player<object2D<float>>
{
public:
	Player2D() {};
	Player2D(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		obj = new object2D<float>;
		obj->name = _name;
		obj->shape = _rect;
		obj->type = _type;
	}
	~Player2D()
	{
		if (obj != nullptr)
		{
			delete obj;
			obj = nullptr;
		}
	}

public:
	void frame(float _dt) override
	{
		obj->accel = obj->force / obj->mass;
		obj->velocity += obj->accel * _dt;
		float resistCoef = -0.1f;
		Vector2f resistForce = obj->force * resistCoef * _dt;
		obj->force += resistForce;

		obj->shape.offset(obj->velocity.x, obj->velocity.y);
	}
};

class Player3D : public Player<object3D<float>>
{
public:
	Player3D() {};
	Player3D(std::string _name, Box_<float> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		obj->name = _name;
		obj->shape = _box;
		obj->type = _type;
	}
	~Player3D()
	{
		if (obj != nullptr)
		{
			delete obj;
			obj = nullptr;
		}
	};

public:
	void frame(float _dt) override
	{
		obj->accel = obj->force / obj->mass;
		obj->velocity += obj->accel * _dt;
		float resistCoef = -0.1f;
		Vector3f resistForce = obj->force * resistCoef * _dt;
		obj->force += resistForce;

		obj->shape.offset(obj->velocity.x, obj->velocity.y, obj->velocity.z);
	}
};