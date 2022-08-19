#pragma once
#include "Object.hpp"

template <class ObjectDimension>
class Obstacle
{
protected:
	ObjectDimension* obj = nullptr;
};

class Obstacle2D : public Obstacle<object2D<float>>
{
public:
	Obstacle2D() 
	{ 
		obj = new object2D<float>; 
	};
	Obstacle2D(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		obj = new object2D<float>;
		obj->name = _name;
		obj->shape = _rect;
		obj->type = _type;
	}
};

class Obstacle3D : public Obstacle<object3D<float>>
{
public:
	Obstacle3D() 
	{ 
		obj = new object3D<float>;
	};
	Obstacle3D(std::string _name, Box_<float> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		obj = new object3D<float>;
		obj->name = _name;
		obj->shape = _box;
		obj->type = _type;
	}
};