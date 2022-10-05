#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"

enum class MapObjectType
{
	Floor,
	Rope,
	RopeRadder,
	Portal,
};

class MapObject : public object2D<float>
{
public:
	MapObjectType type = MapObjectType::Floor;
	bool isPierce = true;

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