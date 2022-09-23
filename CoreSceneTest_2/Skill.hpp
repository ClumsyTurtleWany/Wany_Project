#pragma once
#include "Object.hpp"
#include "Camera.hpp"

class Skill : public object2D<float>
{
public:
	//object2D<float>* pObj;
	//Camera* renderCamera;

public:
	Skill();
	Skill(const Rect2f& _rect);
	virtual ~Skill();

public:
	void setCamera(Camera* _camera);
};