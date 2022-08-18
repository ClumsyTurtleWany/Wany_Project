#pragma once
#include "Object3D.hpp"

class NPC3D : public object3D<float>
{
public:
	NPC3D() {};
	NPC3D(std::string _name, Box_<float> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
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
		float resistCoef = -0.2f;
		Vector3f resistForce = force * resistCoef * _dt;
		force += resistForce;

		box.offset(velocity.dx, velocity.dy, velocity.dz);
	}
};