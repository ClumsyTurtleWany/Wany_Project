#pragma once
#include "Object3D.hpp"

class Player3D : public object3D<float>
{
public:
	Player3D() {};
	Player3D(std::string _name, Box_<float> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		name = _name;
		box = _box;
		type = _type;
	}

public:
	void frame(float _dt) override
	{
		accel = force / mass;
		velocity += accel * _dt;
		float resistCoef = -0.1f;
		Vector3f resistForce = force * resistCoef * _dt;
		force += resistForce;

		box.offset(velocity.x, velocity.y, velocity.z);
	}
};