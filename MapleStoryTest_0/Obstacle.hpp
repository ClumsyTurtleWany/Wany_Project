#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"

enum class ObstacleType
{
	Map,
	Rope,
	RopeRadder,
	Slope
};

class Obstacle : public object2D<float>
{
public:
	ObstacleType type = ObstacleType::Map;

//public:
//	Obstacle();
//	Obstacle(const Rect2f& _rect);
//	virtual ~Obstacle();
//
//public:
//	virtual bool initialize();
//	virtual bool frame(float _dt);
//	virtual bool render();
//	virtual bool release();
};