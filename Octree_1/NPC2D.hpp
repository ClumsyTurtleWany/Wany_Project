#pragma once
#include "Object2D.hpp"

class NPC2D : public object2D<float>
{
public:
	NPC2D() {};
	NPC2D(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
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
		float resistCoef = -0.2f;
		Vector2f resistForce = force * resistCoef * _dt;
		force += resistForce;

		rect.offset(velocity.x, velocity.y);
	}
};