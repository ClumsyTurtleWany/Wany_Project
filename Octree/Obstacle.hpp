#pragma once
#include "Object.hpp"

class Obstacle : public object<float>
{
public:
	Obstacle() {};
	Obstacle(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		name = _name;
		rect = _rect;
		type = _type;
	}
};