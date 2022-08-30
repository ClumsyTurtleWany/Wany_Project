#pragma once
#include "Object.hpp"

template <typename T>
class Player2D : public object2D<T> //: public Player<object2D<T>>
{
public:
	Player2D() 
	{
		this->type = OBJECT_TYPE::DYNAMIC_OBJECT;
	};
	Player2D(std::string _name, Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->name = _name;
		this->shape = _rect;
		this->type = _type;
	}
	~Player2D() {};

public:
	bool frame(float _dt) override
	{
		this->accel = this->force / this->mass;
		this->velocity += this->accel * _dt;
		float resistCoef = -0.1f;
		Vector2D_<T> resistForce = this->force * resistCoef * _dt;
		this->force += resistForce;

		this->shape.offset(this->velocity.x, this->velocity.y);

		this->updateShader();

		return true;
	}
};

template <typename T>
class Player3D : public object3D<T> //: public Player<object3D<T>>
{
public:
	Player3D()
	{
		this->type = OBJECT_TYPE::DYNAMIC_OBJECT;
	};

	Player3D(std::string _name, Box_<T> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->name = _name;
		this->shape = _box;
		this->type = _type;
	}
	~Player3D() {};

public:
	bool frame(float _dt) override
	{
		this->accel = this->force / this->mass;
		this->velocity += this->accel * _dt;
		float resistCoef = -0.1f;
		Vector3D_<T> resistForce = this->force * resistCoef * _dt;
		this->force += resistForce;

		this->shape.offset(this->velocity.x, this->velocity.y, this->velocity.z);

		return true;
	}
};