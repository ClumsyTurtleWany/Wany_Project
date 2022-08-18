#pragma once
#include "Object2D.hpp"

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