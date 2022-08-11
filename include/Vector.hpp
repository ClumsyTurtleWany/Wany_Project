#pragma once
#include "Geometry.hpp"

template <typename T>
class Vector2D_
{
public:
	union
	{
		struct
		{
			T x;
			T y;
		};
		T v[2];
	};
	
public:
	Vector2D_() : x(0), y(0) {};
	Vector2D_(const T& _x, const T& _y) : x(_x), y(_y) {};
	Vector2D_(const Vector2D_<T>& _v) : x(_v.x), y(_v.y) {};
	~Vector2D_() {};

	Vector2D_<T> operator +(const Vector2D_<T>& _v)
	{
		return Vector2D_<T>(x + _v.x, y + _v.y);
	}

	Vector2D_<T> operator - (const Vector2D_<T>& _v)
	{
		return Vector2D_<T>(x - _v.x, y - _v.y);
	}

	Vector2D_<T> operator *(const T& _val)
	{
		return Vector2D_<T>(x * _val, y * _val);
	}

	void operator +=(const Vector2D_<T>& _v)
	{
		x += _v.x;
		y += _v.y;
	}

	void operator -=(const Vector2D_<T>& _v)
	{
		x -= _v.x;
		y -= _v.y;
	}

	void operator *=(const T& _val)
	{
		x *= _val;
		y *= _val;
	}

	bool operator ==(const Vector2D_<T>& _v)
	{
		if ((x == _v.x) && (y == _v.y))
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
		if ((x != _v.x) || (y != _v.y))
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
		return sqrt(static_cast<float>(x * x + y * y));
	}
	// 정규화: 단위벡터(자신을) 계산
	void normalized()
	{
		this = unit();
	}
	// 단위벡터 반환 normal == unit
	const Vector2D_<T> unit()
	{
		return Vector2D_<T>(x / x, y / y);
	}

	float angle(const Vector2D_<T>& _v)
	{
		Vector2D_<T> a = unit();
		Vector2D_<T> b = _v.unit();
		float cosTheta = a.x * b.x + a.y * b.y; // 내적
		float degree = RadianToDegree(acos(cosTheta));
		return angle;
	}
};

using Vector = Vector2D_<int>;
using Vector2D = Vector2D_<int>;