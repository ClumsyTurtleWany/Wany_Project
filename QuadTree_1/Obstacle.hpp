#include "..\MapleStoryTest_0\Obstacle.hpp"
#include "..\MapleStoryTest_0\Obstacle.hpp"
#pragma once
#include "Object.hpp"

class Obstacle : public object<float>
{
public:
	Obstacle() {}
	inline Obstacle::Obstacle(const Rect2f& _rect)
	{
	}
	inline Obstacle::~Obstacle()
	{
	}
	;
	Obstacle(std::string _name, Rect2f _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		name = _name;
		rect = _rect;
		type = _type;
	}
};