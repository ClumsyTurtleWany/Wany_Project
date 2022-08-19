#pragma once
#include "Object.hpp"

class NPC2D : public object2D<float>
{
public:
	NPC2D() {};
	NPC2D(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		name = _name;
		shape = _rect;
		type = _type;
	}

public:
	void frame(float _dt) override
	{
		accel = force / mass;
		velocity += accel * _dt;
		float resistCoef = -0.2f;
		Vector2f resistForce = force * resistCoef * _dt;
		force += resistForce;

		shape.offset(velocity.x, velocity.y);
	}
};

class NPC3D : public object3D<float>
{
public:
	NPC3D() {};
	NPC3D(std::string _name, Box_<float> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		name = _name;
		shape = _box;
		type = _type;
	}

public:
	void frame(float _dt) override
	{
		accel = force / mass;
		velocity += accel * _dt;
		float resistCoef = -0.2f;
		Vector3f resistForce = force * resistCoef * _dt;
		force += resistForce;

		shape.offset(velocity.x, velocity.y, velocity.z);
	}
};