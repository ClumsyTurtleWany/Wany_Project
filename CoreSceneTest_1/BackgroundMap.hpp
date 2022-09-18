#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"
#include "Camera.hpp"

class BackgroundMap : public object2D<float>
{
public:
	//object2D<float>* pObj;
	Camera* renderCamera;

public:
	BackgroundMap();
	BackgroundMap(const Rect2f& _rect);
	virtual ~BackgroundMap();

public:
	virtual void updateShader() override;
//public:
//	virtual bool initialize();
//	virtual bool frame(float _dt);
//	virtual bool render();
//	virtual bool release();

};