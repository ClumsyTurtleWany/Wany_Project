#pragma once
#include "Point.hpp"

template <typename T>
class Vector2D_
{
public:
	Point_<T> pos;
	union
	{
		struct
		{
			T dx;
			T dy;
		};
		T v[2];
	};
	
public:
	Vector2D_() : pos(Point_<T>()), dx(0), dy(0) {};
	Vector2D_(const T& _dx, const T& _dy) : dx(_dx), dy(_dy) {};
	Vector2D_(const Point_<T>& _pos, const T& _dx, const T& _dy) : pos(_pos), dx(_dx), dy(_dy) {};
	Vector2D_(const Vector2D_<T>& _v) : pos(_v.pos), dx(_v.dx), dy(_v.dy) {};
	~Vector2D_() {};

	Vector2D_<T> operator +(const Vector2D_<T>& _v)
	{
		return Vector2D_<T>(dx + _v.dx, dy + _v.dy);
	}

	Vector2D_<T> operator - (const Vector2D_<T>& _v)
	{
		return Vector2D_<T>(dx - _v.dx, dy - _v.dy);
	}

	Vector2D_<T> operator *(const T& _val)
	{
		return Vector2D_<T>(dx * _val, dy * _val);
	}

	Vector2D_<T> operator /(const T& _val)
	{
		return Vector2D_<T>(dx / _val, dy / _val);
	}

	void operator +=(const Vector2D_<T>& _v)
	{
		dx += _v.dx;
		dy += _v.dy;
	}

	void operator -=(const Vector2D_<T>& _v)
	{
		dx -= _v.dx;
		dy -= _v.dy;
	}

	void operator *=(const T& _val)
	{
		dx *= _val;
		dy *= _val;
	}

	void operator /=(const T& _val)
	{
		dx /= _val;
		dy /= _val;
	}

	bool operator ==(const Vector2D_<T>& _v)
	{
		if ((pos == _v.pos) && (dx == _v.dx) && (dy == _v.dy))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Vector2D_<T>& _v)
	{
		if ((pos != _v.pos) || (dx != _v.dx) || (dy != _v.dy))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <(const Vector2D_<T>& _v)
	{
		if ((dx < _v.dx) && (dy < _v.dy))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >(const Vector2D_<T>& _v)
	{
		if ((dx > _v.dx) && (dy > _v.dy))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <=(const Vector2D_<T>& _v)
	{
		if ((dx <= _v.dx) && (dy <= _v.dy))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >=(const Vector2D_<T>& _v)
	{
		if ((dx >= _v.dx) && (dy >= _v.dy))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	float length()
	{
		return sqrt(static_cast<float>(dx * dx + dy * dy));
	}
	// 정규화: 단위벡터(자신을) 계산
	void normalized()
	{
		this = unit();
	}
	// 단위벡터 반환 normal == unit
	const Vector2D_<T> unit()
	{
		return Vector2D_<T>(dx / dx, dy / dy);
	}

	float angle(const Vector2D_<T>& _v)
	{
		Vector2D_<T> a = unit();
		Vector2D_<T> b = _v.unit();
		float cosTheta = a.dx * b.dx + a.dy * b.dy; // 내적
		float degree = RadianToDegree(acos(cosTheta));
		return degree;
	}
};

template <typename T>
class Vector3D_
{
public:
	Point3D_<T> pos;
	union
	{
		struct
		{
			T dx;
			T dy;
			T dz;
		};
		T v[3];
	};

public:
	Vector3D_() : pos(Point3D_<T>()), dx(0), dy(0), dz(0) {};
	Vector3D_(const T& _dx, const T& _dy, const T& _dz) : dx(_dx), dy(_dy), dz(_dz) {};
	Vector3D_(const Vector3D_<T>& _v) : dx(_v.dx), dy(_v.dy), dz(_v.dz) {};
	~Vector3D_() {};

	Vector3D_<T> operator +(const Vector3D_<T>& _v)
	{
		return Vector3D_<T>(dx + _v.dx, dy + _v.dy, dz + _v.dz);
	}

	Vector3D_<T> operator - (const Vector3D_<T>& _v)
	{
		return Vector3D_<T>(dx - _v.dx, dy - _v.dy, dz - _v.dz);
	}

	Vector3D_<T> operator *(const T& _val)
	{
		return Vector3D_<T>(dx * _val, dy * _val, dz * _val);
	}

	Vector3D_<T> operator /(const T& _val)
	{
		return Vector3D_<T>(dx / _val, dy / _val, dz / _val);
	}

	void operator +=(const Vector3D_<T>& _v)
	{
		dx += _v.dx;
		dy += _v.dy;
		dz += _v.dz;
	}

	void operator -=(const Vector3D_<T>& _v)
	{
		dx -= _v.dx;
		dy -= _v.dy;
		dz -= _v.dz;
	}

	void operator *=(const T& _val)
	{
		dx *= _val;
		dy *= _val;
		dz *= _val;
	}

	void operator /=(const T& _val)
	{
		dx /= _val;
		dy /= _val;
		dz /= _val;
	}

	bool operator ==(const Vector3D_<T>& _v)
	{
		if ((pos == _v.pos) && (dx == _v.dx) && (dy == _v.dy) && (dz == _v.dz))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Vector3D_<T>& _v)
	{
		if ((pos != _v.pos) || (dx != _v.dx) || (dy != _v.dy) || (dz != _v.dz))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <(const Vector3D_<T>& _v)
	{
		if ((dx < _v.dx) && (dy < _v.dy) && (dz < _v.dz))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >(const Vector3D_<T>& _v)
	{
		if ((dx > _v.dx) && (dy > _v.dy) && (dz > _v.dz))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <=(const Vector3D_<T>& _v)
	{
		if ((dx <= _v.dx) && (dy <= _v.dy) && (dz <= _v.dz))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >=(const Vector3D_<T>& _v)
	{
		if ((dx >= _v.dx) && (dy >= _v.dy) && (dz >= _v.dz))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	float length()
	{
		return sqrt(static_cast<float>(dx * dx + dy * dy + dz * dz));
	}
	// 정규화: 단위벡터(자신을) 계산
	void normalized()
	{
		this = unit();
	}
	// 단위벡터 반환 normal == unit
	const Vector3D_<T> unit()
	{
		return Vector3D_<T>(dx / dx, dy / dy, dz / dz);
	}

	float angle(const Vector3D_<T>& _v)
	{
		Vector3D_<T> a = unit();
		Vector3D_<T> b = _v.unit();
		float cosTheta = a.dx * b.dx + a.dy * b.dy + a.dz * b.dz; // 내적
		float degree = RadianToDegree(acos(cosTheta));
		return degree;
	}
};

using Vector = Vector2D_<int>;
using Vector2D = Vector2D_<int>;
using Vector2f = Vector2D_<float>;
using Vector3D = Vector3D_<int>;
using Vector3f = Vector3D_<float>;