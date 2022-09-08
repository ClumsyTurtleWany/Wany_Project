#pragma once
#include "Node.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"

class SpaceDivision
{
public:
	SpaceDivision() {};
	virtual ~SpaceDivision() {};

public:
	virtual void create(void* _shape) = 0;
	virtual void addObject(objectBase* _obj) = 0;
	virtual objectBase* newPlayer() = 0;
	virtual objectBase* newNPC() = 0;
	virtual objectBase* newObstacle() = 0;
	virtual bool Collision(objectBase* _src, std::vector<objectBase*>* _dst, std::vector<void*>* _dstSection = nullptr) = 0;
	virtual void updateDynamicObject() = 0;
	virtual bool checkBorder(objectBase* _target) = 0;
};
