#pragma once
#include "Geometry.hpp"

template <typename T>
class Point_
{
public:
	T x = 0;
	T y = 0;

public:
	Point_() {};
	Point_(T _x, T _y) : x(_x), y(_y) {};

	void operator =(const Point_<T>& _pt)
	{
		x = _pt.x;
		y = _pt.y;
	}

	Point_<T> operator +(const Point_<T>& _pt)
	{
		return Point_<T>(x + _pt.x, y + _pt.y);
	}

	Point_<T> operator +(const T& _val)
	{
		return Point_<T>(x + _val, y + _val);
	}

	void operator +=(const Point_<T>& _pt)
	{
		x += _pt.x;
		y += _pt.y;
	}

	void operator +=(const T& _val)
	{
		x += _val;
		y += _val;
	}

	Point_<T> operator -(const Point_<T>& _pt)
	{
		return Point_<T>(x - _pt.x, y - _pt.y);
	}

	Point_<T> operator -(const T& _val)
	{
		return Point_<T>(x - _val, y - _val);
	}

	void operator -=(const Point_<T>& _pt)
	{
		x -= _pt.x;
		y -= _pt.y;
	}

	void operator -=(const T& _val)
	{
		x -= _val;
		y -= _val;
	}

	bool operator ==(const Point_<T>& _pt)
	{
		//if ((x == _pt.x) && (y == _pt.y))
		if ((fabs(x - _pt.x) < 0.001) && (fabs(y - _pt.y) < 0.001))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Point_<T>& _pt)
	{
		//if ((x != _pt.x) || (y != _pt.y))
		if ((fabs(x - _pt.x) > 0.001) || (fabs(y - _pt.y) < 0.001))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <(const Point_<T>& _pt)
	{
		if ((x < _pt.x) && (y < _pt.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >(const Point_<T>& _pt)
	{
		if ((x > _pt.x) && (y > _pt.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <=(const Point_<T>& _pt)
	{
		if ((x <= _pt.x) && (y <= _pt.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >=(const Point_<T>& _pt)
	{
		if ((x >= _pt.x) && (y >= _pt.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

template <typename T>
class Point3D_
{
public:
	T x = 0;
	T y = 0;
	T z = 0;

public:
	Point3D_() {};
	Point3D_(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};

	void operator =(const Point3D_<T>& _pt)
	{
		x = _pt.x;
		y = _pt.y;
		z = _pt.z;
	}

	Point3D_<T> operator +(const Point3D_<T>& _pt)
	{
		return Point3D(x + _pt.x, y + _pt.y, z + _pt.z);
	}

	Point3D_<T> operator +(const T& _val)
	{
		return Point3D(x + _val, y + _val, z + _val);
	}

	void operator +=(const Point3D_<T>& _pt)
	{
		x += _pt.x;
		y += _pt.y;
		z += _pt.z;
	}

	void operator +=(const T& _val)
	{
		x += _val;
		y += _val;
		z += _val;
	}

	Point3D_<T> operator -(const Point3D_<T>& _pt)
	{
		return Point3D_<T>(x - _pt.x, y - _pt.y, z - _pt.z);
	}

	Point3D_<T> operator -(const T& _val)
	{
		return Point3D_<T>(x - _val, y - _val, z - _val);
	}

	void operator -=(const Point3D_<T>& _pt)
	{
		x -= _pt.x;
		y -= _pt.y;
		z -= _pt.z;
	}

	void operator -=(const T& _val)
	{
		x -= _val;
		y -= _val;
		z -= _val;
	}

	bool operator ==(const Point3D_<T>& _pt)
	{
		//if ((x == _pt.x) && (y == _pt.y) && (z == _pt.z))
		if ((fabs(x - _pt.x) < 0.001) && (fabs(y - _pt.y) < 0.001) && (fabs(z - _pt.z) < 0.001))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Point3D_<T>& _pt)
	{
		//if ((x != _pt.x) || (y != _pt.y) || (z != _pt.z))
		if ((fabs(x - _pt.x) > 0.001) || (fabs(y - _pt.y) < 0.001) || (fabs(z - _pt.z) < 0.001))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <(const Point3D_<T>& _pt)
	{
		if ((x < _pt.x) && (y < _pt.y) && (z < _pt.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >(const Point3D_<T>& _pt)
	{
		if ((x > _pt.x) && (y > _pt.y) && (z > _pt.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <=(const Point3D_<T>& _pt)
	{
		if ((x <= _pt.x) && (y <= _pt.y) && (z <= _pt.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >=(const Point3D_<T>& _pt)
	{
		if ((x >= _pt.x) && (y >= _pt.y) && (z >= _pt.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

using Point = Point_<int>;
using Point2D = Point_<int>;
using Point2f = Point_<float>;
using Point3D = Point3D_<int>;
using Point3f = Point3D_<float>;