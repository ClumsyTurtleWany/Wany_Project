#pragma once
#include "Object.hpp"

template <class ObjectDimension>
class Player
{
protected: 
	ObjectDimension* obj = nullptr;

public:
	ObjectDimension* getObject()
	{
		return obj;
	}

	virtual void frame(float _dt) = 0;
};

template <typename T>
class Player2D : public Player<object2D<T>>
{
public:
	Player2D() {};
	Player2D(std::string _name, Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->obj = new object2D<T>;
		this->obj->name = _name;
		this->obj->shape = _rect;
		this->obj->type = _type;
	}
	~Player2D()
	{
		if (this->obj != nullptr)
		{
			delete this->obj;
			this->obj = nullptr;
		}
	}

public:
	void frame(float _dt) override
	{
		this->obj->accel = this->obj->force / this->obj->mass;
		this->obj->velocity += this->obj->accel * _dt;
		float resistCoef = -0.1f;
		Vector2D_<T> resistForce = this->obj->force * resistCoef * _dt;
		this->obj->force += resistForce;

		this->obj->shape.offset(this->obj->velocity.x, this->obj->velocity.y);
	}
};

template <typename T>
class Player3D : public Player<object3D<T>>
{
public:
	Player3D() {};
	Player3D(std::string _name, Box_<T> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->obj = new object3D<T>;
		this->obj->name = _name;
		this->obj->shape = _box;
		this->obj->type = _type;
	}
	~Player3D()
	{
		if (this->obj != nullptr)
		{
			delete this->obj;
			this->obj = nullptr;
		}
	};

public:
	void frame(float _dt) override
	{
		this->obj->accel = this->obj->force / this->obj->mass;
		this->obj->velocity += this->obj->accel * _dt;
		float resistCoef = -0.1f;
		Vector3D_<T> resistForce = this->obj->force * resistCoef * _dt;
		this->obj->force += resistForce;

		this->obj->shape.offset(this->obj->velocity.x, this->obj->velocity.y, this->obj->velocity.z);
	}
};