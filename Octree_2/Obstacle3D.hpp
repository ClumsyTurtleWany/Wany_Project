#pragma once
#include "Object3D.hpp"

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