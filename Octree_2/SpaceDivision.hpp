#pragma once
#include "Node.hpp"

template <class Shape, class ObjectDimension>
class SpaceDivision
{
public:
	SpaceDivision() {};
	virtual ~SpaceDivision() {};
public:
	virtual void create(Shape _shape) = 0;
	virtual void addObject(ObjectDimension* _obj) = 0;
	virtual bool Collision(ObjectDimension* _src, std::vector<ObjectDimension*>* _dst, std::vector<Shape>* _dstSection = nullptr) = 0;

	// Common
	virtual void updateDynamicObject() = 0;
};
