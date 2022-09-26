#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"

enum class MapObjectType
{
	Floor,
	Rope,
	RopeRadder,
};

class MapObject : public object2D<float>
{
public:
	MapObjectType type = MapObjectType::Floor;

public:
	MapObject();
	MapObject(const Rect2f& _rect, MapObjectType _type);
	virtual ~MapObject();

//public:
//	virtual bool initialize();
//	virtual bool frame(float _dt);
//	virtual bool render();
//	virtual bool release();
};