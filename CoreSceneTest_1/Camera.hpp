#pragma once
#include "Define.hpp"

class Camera
{
private:
	Vector2f pos;
	float width = 0.0f;
	float height = 0.0f;
	Rect2f rect;
	Rect2f boundary;

public:
	void setPos(const Vector2f& _pos);
	void setWidth(float _width);
	void setHeight(float _height);
	void setBoundary(const Rect2f& _boundaryRect);

	Rect2f getRect();
	Vector2f getPos();
	float getWidth();
	float getHeight();

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};