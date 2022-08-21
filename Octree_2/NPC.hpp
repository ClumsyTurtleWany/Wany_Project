#pragma once
#include "Object.hpp"

template <typename T>
class NPC2D : public object2D<T>
{
public:
	NPC2D() {};
	NPC2D(std::string _name, Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->name = _name;
		this->shape = _rect;
		this->type = _type;
	}

public:
	void frame(float _dt) override
	{
		this->accel = this->force / this->mass;
		this->velocity += this->accel * _dt;
		float resistCoef = -0.2f;
		Vector2D_<T> resistForce = this->force * resistCoef * _dt;
		this->force += resistForce;

		this->shape.offset(this->velocity.x, this->velocity.y);
	}
};

template <typename T>
class NPC3D : public object3D<T>
{
public:
	NPC3D() {};
	NPC3D(std::string _name, Box_<T> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->name = _name;
		this->shape = _box;
		this->type = _type;
	}

public:
	void frame(float _dt) override
	{
		this->accel = this->force / this->mass;
		this->velocity += this->accel * _dt;
		float resistCoef = -0.2f;
		Vector3D_<T> resistForce = this->force * resistCoef * _dt;
		this->force += resistForce;

		this->shape.offset(this->velocity.x, this->velocity.y, this->velocity.z);
	}
};