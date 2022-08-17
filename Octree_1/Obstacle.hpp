#pragma once
#include "Object.hpp"

class Obstacle2D : public object2D<float>
{
public:
	Obstacle2D() {};
	Obstacle2D(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		name = _name;
		rect = _rect;
		type = _type;
	}
};

class Obstacle3D : public object3D<float>
{
public:
	Obstacle3D() {};
	Obstacle3D(std::string _name, Box_<float> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		name = _name;
		box = _box;
		type = _type;
	}
};