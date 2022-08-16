#pragma once
#include "Point.hpp"

template <typename T>
class Box_
{
public:
	Point3D_<T> pos = Point3D_<T>();
	T width = 0.0;
	T height = 0.0;
	T depth = 0.0;
	float theta = 0.0f;
	float pi = 0.0f;

public:
	Box_() {};

	Box_(T _x, T _y, T _z, T _width, T _height, T _depth, float _theta = 0.0f, float _pi = 0.0f)
	{
		pos = Point3D_<T>(_x, _y, _z);
		width = _width;
		height = _height;
		depth = _depth;
		theta = _theta;
		pi = _pi;
	}

	Box_(Point3D_<T> _pos, T _width, T _height, T _depth, float _theta = 0.0f, float _pi = 0.0f)
	{
		pos = _pos;
		width = _width;
		height = _height;
		depth = _depth;
		theta = _theta;
		pi = _pi;
	}

	~Box_() {};

public:
	bool operator ==(const Box_<T>& _box)
	{
		if ((pos == _box.pos) &&
			(width == _box.width) &&
			(height == _box.height) &&
			(depth == _box.depth) &&
			(theta == _box.theta) &&
			(pi == _box.pi))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Box_<T>& _box)
	{
		if ((pos != _box.pos) ||
			(width != _box.width) ||
			(height != _box.height) ||
			(depth != _box.depth) ||
			(theta != _box.theta) ||
			(pi != _box.pi))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	Point3D_<T> center() const
	{
		return Point3D_<T>(pos.x + (width / 2.0f), pos.y + (height / 2.0f), pos.z + (depth / 2.0f));
	}

	Point3D_<T> maxp() const
	{
		return Point3D_<T>(pos.x + width, pos.y + height, pos.z + depth);
	}

	float length() const
	{
		return sqrt(width * width + height * height + depth * depth);
	}

	void offset(Point3D_<T> _offset)
	{
		pos += _offset;
	}

	void offset(T _dx, T _dy, T _dz)
	{
		pos += Point3D_<T>(_dx, _dy, _dz);
	}

	bool BoxInBox(const Box_<T>& _box)
	{
		if ((pos <= _box.pos) && (maxp() > _box.maxp()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool intersectBox(const Box_<T> _box, Box_<T>* _dst = nullptr)
	{
		Point3D_<T> unionLT, unionRB;
		unionLT.x = pos.x < _box.pos.x ? pos.x : _box.pos.x;
		unionLT.y = pos.y < _box.pos.y ? pos.y : _box.pos.y;
		unionLT.z = pos.z < _box.pos.z ? pos.z : _box.pos.z;

		unionRB.x = maxp().x < _box.maxp().x ? _box.maxp().x : maxp().x;
		unionRB.y = maxp().y < _box.maxp().y ? _box.maxp().y : maxp().y;
		unionRB.z = maxp().z < _box.maxp().z ? _box.maxp().z : maxp().z;

		Box_<T> unionBox(unionLT, unionRB.x - unionLT.x, unionRB.y - unionLT.y, unionRB.z - unionLT.z);
		if ((unionBox.width < (width + _box.width)) && (unionBox.height < (height + _box.height)) && (unionBox.depth < (depth + _box.depth)))
		{
			if (_dst != nullptr)
			{
				// intersection
				Point3D_<T> interLT, interRB;
				_dst->pos.x = pos.x < _box.pos.x ? _box.pos.x : pos.x;
				_dst->pos.y = pos.y < _box.pos.y ? _box.pos.y : pos.y;
				_dst->pos.z = pos.z < _box.pos.z ? _box.pos.z : pos.z;

				interRB.x = maxp().x < _box.maxp().x ? maxp().x : _box.maxp().x;
				interRB.y = maxp().y < _box.maxp().y ? maxp().y : _box.maxp().y;
				interRB.z = maxp().y < _box.maxp().z ? maxp().y : _box.maxp().z;

				_dst->width = interRB.x - _dst->pos.x;
				_dst->height = interRB.y - _dst->pos.y;
				_dst->depth = interRB.z - _dst->pos.z;
			}
			return true;
		}
		else
		{
			return false;
		}

	}
};

using Box = Box_<float>;