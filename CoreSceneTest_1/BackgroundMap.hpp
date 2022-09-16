#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"

class BackgroundMap
{
public:
	object2D<float>* pObj;

public:
	BackgroundMap();
	BackgroundMap(const Rect2f& _rect);
	virtual ~BackgroundMap();

public:
	virtual bool initialize();
	virtual bool frame(float _dt);
	virtual bool render();
	virtual bool release();
};