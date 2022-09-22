#include "Camera.hpp"

Rect2f Camera::getRect()
{
	return rect;
}

void Camera::setPos(const Vector2f& _pos)
{
	pos = _pos;
}

void Camera::setWidth(float _width)
{
	width = _width;
}

void Camera::setHeight(float _height)
{
	height = _height;
}

void Camera::setBoundary(const Rect2f& _boundaryRect)
{
	boundary = _boundaryRect;
}

Vector2f Camera::getPos()
{
	return pos;
}

float Camera::getWidth()
{
	return width;
}

float Camera::getHeight()
{
	return height;
}

bool Camera::initialize()
{
	return true;
}

bool Camera::frame()
{
	float x = pos.x - (width * 0.5f) < 0 ? 0 : pos.x - (width * 0.5f);
	float y = pos.y - (height * 0.5f) < 0 ? 0 : pos.y - (height * 0.5f);

	if (x + width > boundary.RB.x)
	{
		x = boundary.RB.x - width;
	}

	if (y + height > boundary.RB.y)
	{
		y = boundary.RB.y - height;
	}

	rect = Rect2f(x, y, width, height);	 

	return true;
}

bool Camera::render()
{
	return true;
}

bool Camera::release()
{
	return true;
}
