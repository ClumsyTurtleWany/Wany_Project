#pragma once
#include "Object.hpp"

class NPC : public object<float>
{
public:
	NPC() {};
	NPC(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		name = _name;
		rect = _rect;
		type = _type;
	}

public:
	void frame(float _dt) override
	{
		accel = force / mass;
		velocity += accel * _dt;
		float resistCoef = -0.2;
		Vector2f resistForce = force * resistCoef * _dt;
		force += resistForce;

		rect.offset(velocity.dx, velocity.dy);
	}
};