#pragma once
#include "Point.hpp"

template <typename T>
class Circle_
{
public:
	Point_<T> c;
	T radius = 0;

public:
	Circle_() {};
	Circle_(Point_<T> _pos, T _rad) : c(_pos), radius(_rad) {};
	Circle_(T _x, T _y, T _rad)
	{
		c = (_x, _y);
		radius = _rad;
	};
	Circle_(const Rect_<T>& _src)
	{
		// Circumscribed circle
		c = _src.center();
		T diameter = static_cast<T>(ceil(sqrt(pow(_src.width(), 2) + pow(_src.height(), 2))));
		radius = static_cast<T>(diameter / 2.0f);
	}
	~Circle_() {};

	bool operator ==(const Circle_<T>& _circle)
	{
		if ((c == _circle.c) && (radius == _circle.radius))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Circle_<T>& _circle)
	{
		if ((c != _circle.c) || (radius != _circle.radius))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	T diameter()	const { return static_cast<T>(radius * 2.0f); }
	T area()		const { return static_cast<T>(PI * radius * radius); }

	void offset(const Point_<T>& _offset)
	{
		c += _offset;
	}

	void offset(const T& _x, const T& _y)
	{
		c += (_x, _y);
	}

	bool intersectCircle(const Circle_<T>& _src)
	{
		double x = static_cast<double>(_src.c.x) - static_cast<double>(c.x);
		double y = static_cast<double>(_src.c.y) - static_cast<double>(c.y);
		T distance = static_cast<T>(sqrt(pow(x, 2.0) + pow(y, 2.0)));
		if (distance <= (radius + _src.radius))
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
class Sphere_
{
public:
	Point3D_<T> c;
	T radius = 0;

public:
	Sphere_() {};
	Sphere_(Point3D_<T> _pos, T _rad) : c(_pos), radius(_rad) {};
	Sphere_(T _x, T _y, T _z, T _rad)
	{
		c = (_x, _y, _z);
		radius = _rad;
	};
	//Sphere_(const Rect3D_<T>& _src)
	//{
	//	// Circumscribed circle
	//	/*c = _src.center();
	//	T diameter = sqrt(pow(_src.width(), 2) + pow(_src.height(), 2));
	//	radius = static_cast<T>(diameter / 2.0f);*/
	//}
	~Sphere_() {};

	bool operator ==(const Sphere_<T>& _sphere)
	{
		if ((c == _sphere.c) && (radius == _sphere.radius))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Sphere_<T>& _sphere)
	{
		if ((c != _sphere.c) || (radius != _sphere.radius))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	T diameter()	const { return static_cast<T>(radius * 2.0f); }
	T area()		const { return static_cast<T>(4 * PI * radius * radius); }

	void offset(const Point3D_<T>& _offset)
	{
		c += _offset;
	}

	void offset(const T& _x, const T& _y, const T& _z)
	{
		c += (_x, _y, _z);
	}

	bool intersectCircle(const Sphere_<T>& _src)
	{
		T distance = sqrt(pow(_src.c.x - c.x, 2) + pow(_src.c.y - c.y, 2) + pow(_src.c.z - c.z, 2));
		if (distance <= (radius + _src.radius))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};


using Circle = Circle_<int>;
using Circle_f = Circle_<float>;
using Sphere = Sphere_<int>;
using Sphere_f = Sphere_<float>;