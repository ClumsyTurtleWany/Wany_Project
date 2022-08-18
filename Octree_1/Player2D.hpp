#pragma once
#include "Object2D.hpp"

class Player2D : public object2D<float>
{
public:
	Player2D() {};
	Player2D(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
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
		float resistCoef = -0.1f;
		Vector2f resistForce = force * resistCoef * _dt;
		force += resistForce;

		rect.offset(velocity.dx, velocity.dy);
	}
};