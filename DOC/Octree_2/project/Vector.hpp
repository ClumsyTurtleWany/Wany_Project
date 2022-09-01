#pragma once
#include "Point.hpp"

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
	Vector2D_(const T& _dx, const T& _dy) : x(_dx), y(_dy) {};
	Vector2D_(const Point_<T>& _pos) : x(_pos.x), y(_pos.y) {};
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

	Vector2D_<T> operator /(const T& _val)
	{
		return Vector2D_<T>(x / _val, y / _val);
	}

	void operator =(const Point_<T>& _v)
	{
		x += _v.x;
		y += _v.y;
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

	void operator /=(const T& _val)
	{
		x /= _val;
		y /= _val;
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

	bool operator <(const Vector2D_<T>& _v)
	{
		if ((x < _v.x) && (y < _v.y))
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
		if ((x > _v.x) && (y > _v.y))
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
		if ((x <= _v.x) && (y <= _v.y))
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
		if ((x >= _v.x) && (y >= _v.y))
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
	// ����ȭ: ��������(�ڽ���) ���
	void normalized()
	{
		this = unit();
	}
	// �������� ��ȯ normal == unit
	const Vector2D_<T> unit()
	{
		return Vector2D_<T>(x / x, y / y);
	}

	float angle(const Vector2D_<T>& _v)
	{
		Vector2D_<T> a = unit();
		Vector2D_<T> b = _v.unit();
		float cosTheta = a.x * b.x + a.y * b.y; // ����
		float degree = RadianToDegree(acos(cosTheta));
		return degree;
	}
};

template <typename T>
class Vector3D_
{
public:
	union
	{
		struct
		{
			T x;
			T y;
			T z;
		};
		T v[3];
	};

public:
	Vector3D_() : x(0), y(0), z(0) {};
	Vector3D_(const T& _dx, const T& _dy, const T& _dz) : x(_dx), y(_dy), z(_dz) {};
	Vector3D_(const Point_<T>& _pos) : x(_pos.x), y(_pos.y), z(0) {};
	Vector3D_(const Point3D_<T>& _pos) : x(_pos.x), y(_pos.y), z(_pos.z) {};
	Vector3D_(const Vector2D_<T>& _v) : x(_v.x), y(_v.y), z(0) {};
	Vector3D_(const Vector3D_<T>& _v) : x(_v.x), y(_v.y), z(_v.z) {};
	~Vector3D_() {};

	Vector3D_<T> operator +(const Vector3D_<T>& _v)
	{
		return Vector3D_<T>(x + _v.x, y + _v.y, z + _v.z);
	}

	Vector3D_<T> operator - (const Vector3D_<T>& _v)
	{
		return Vector3D_<T>(x - _v.x, y - _v.y, z - _v.z);
	}

	Vector3D_<T> operator *(const T& _val)
	{
		return Vector3D_<T>(x * _val, y * _val, z * _val);
	}

	Vector3D_<T> operator /(const T& _val)
	{
		return Vector3D_<T>(x / _val, y / _val, z / _val);
	}

	void operator =(const Point_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = 0;
	}

	void operator =(const Point3D_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = _v.z;
	}

	void operator =(const Vector2D_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = 0;
	}

	void operator +=(const Vector3D_<T>& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
	}

	void operator -=(const Vector3D_<T>& _v)
	{
		x -= _v.x;
		y -= _v.y;
		z -= _v.z;
	}

	void operator *=(const T& _val)
	{
		x *= _val;
		y *= _val;
		z *= _val;
	}

	void operator /=(const T& _val)
	{
		x /= _val;
		y /= _val;
		z /= _val;
	}

	bool operator ==(const Vector3D_<T>& _v)
	{
		if ((x == _v.x) && (y == _v.y) && (z == _v.z))
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
		if ((x != _v.x) || (y != _v.y) || (z != _v.z))
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
		if ((x < _v.x) && (y < _v.y) && (z < _v.z))
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
		if ((x > _v.x) && (y > _v.y) && (z > _v.z))
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
		if ((x <= _v.x) && (y <= _v.y) && (z <= _v.z))
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
		if ((x >= _v.x) && (y >= _v.y) && (z >= _v.z))
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
		return sqrt(static_cast<float>(x * x + y * y + z * z));
	}
	// ����ȭ: ��������(�ڽ���) ���
	void normalized()
	{
		this = unit();
	}
	// �������� ��ȯ normal == unit
	const Vector3D_<T> unit()
	{
		return Vector3D_<T>(x / x, y / y, z / z);
	}

	float angle(const Vector3D_<T>& _v)
	{
		Vector3D_<T> a = unit();
		Vector3D_<T> b = _v.unit();
		float cosTheta = a.x * b.x + a.y * b.y + a.z * b.z; // ����
		float degree = RadianToDegree(acos(cosTheta));
		return degree;
	}
};

using Vector = Vector2D_<int>;
using Vector2D = Vector2D_<int>;
using Vector2f = Vector2D_<float>;
using Vector3D = Vector3D_<int>;
using Vector3f = Vector3D_<float>;