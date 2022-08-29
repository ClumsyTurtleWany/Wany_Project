#pragma once
#include "Point.hpp"
#include "Box.hpp"

template <typename T>
class Cube_ : public Box_<T>
{
public:
	Cube_() {};

	Cube_(T _x, T _y, T _z, T _size, float _theta = 0.0f, float _pi = 0.0f)
	{
		this->width = this->height = this->depth = _size;
	}

	Cube_(Point3D_<T> _pos, T _size, float _theta = 0.0f, float _pi = 0.0f)
	{
		this->width = this->height = this->depth = _size;
	}
	~Cube_() {};
};