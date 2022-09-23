#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"
#include "Camera.hpp"

class MapObject : public object2D<float>
{
public:
	//object2D<float>* pObj;
	//Camera* renderCamera;

public:
	MapObject();
	MapObject(const Rect2f& _rect);
	virtual ~MapObject();

public:
	virtual void updateShader() override;
	virtual void updateShaderCamera() override;
//public:
//	virtual bool initialize();
//	virtual bool frame(float _dt);
//	virtual bool render();
//	virtual bool release();

};