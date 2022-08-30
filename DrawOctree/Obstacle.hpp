#pragma once
#include "Object.hpp"

template <typename T>
class Obstacle2D : public object2D<T>
{
public:
	Obstacle2D() {};
	Obstacle2D(std::string _name, Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->name = _name;
		this->shape = _rect;
		this->type = _type;
	}

	bool frame(float _dt) 
	{ 
		this->updateShader();
		return true; 
	};
};

template <typename T>
class Obstacle3D : public object3D<T>
{
public:
	Obstacle3D() {};
	Obstacle3D(std::string _name, Box_<T> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->name = _name;
		this->shape = _box;
		this->type = _type;
	}

	bool frame(float _dt) 
	{ 
		return true; 
	};
};