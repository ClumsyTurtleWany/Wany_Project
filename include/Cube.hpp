#pragma once
#include "Point.hpp"

template <typename T>
class Cube_
{
public:
	Point3D_<T> pos;
	Point3D_<T> corner[8];
	T size = 0;
	float theta = 0.0f;
	float pi = 0.0f;
	
public:
	Cube_() {};

	Cube_(T _x, T _y, T _z, T _size, float _theta = 0.0f, float _pi = 0.0f)
	{
		corner[0] = Point3D_<T>(_x, _y, _z);
		corner[1] = Point3D_<T>(cos(_theta) * _x, sin(_theta) * _y;
	}

	Cube_(Point3D_<T> _pos, T _size, float _theta = 0.0f, float _pi = 0.0f)
	{
		corner[0] = _pos;
		corner[1] = Point3D_<T>(cos(_theta) * _pos.x, sin(_theta) * _pos.y;
	}
	~Cube_() {};

public:
	bool operator ==(const Cube_<T>& _cube)
	{
		if ((pos == _cube.pos) &&
			(size == _cube.size) &&
			(theta == _cube.theta) &&
			(pi == _cube.pi))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Cube_<T>& _cube)
	{
		if ((pos != _cube.pos) ||
			(size != _cube.size) ||
			(theta != _cube.theta) ||
			(pi != _cube.pi))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};