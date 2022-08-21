#pragma once
#include "Node.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"

template <class Shape, class ObjectDimension>
class SpaceDivision
{
protected:
	node<Shape, ObjectDimension>* root = nullptr;

public:
	SpaceDivision() {};
	virtual ~SpaceDivision() {};

public:
	virtual void create(Shape _shape) = 0;
	virtual void addObject(ObjectDimension* _obj) = 0;
	virtual ObjectDimension* newNPC() = 0;
	virtual ObjectDimension* newObstacle() = 0;
	virtual bool Collision(ObjectDimension* _src, std::vector<ObjectDimension*>* _dst, std::vector<Shape>* _dstSection = nullptr) = 0;
	virtual void updateDynamicObject() = 0;
	virtual bool checkBorder(ObjectDimension* _target) = 0;
};
