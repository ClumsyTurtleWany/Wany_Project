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
	Vector2D_(const T& _x, const T& _y) : x(_x), y(_y) {};
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

	/*void operator =(const Point_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
	}*/

	void operator =(const Vector2D_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
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
	Vector3D_(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {};
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

	/*void operator =(const Point_<T>& _v)
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
	}*/

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
	// 정규화: 단위벡터(자신을) 계산
	void normalized()
	{
		this = unit();
	}
	// 단위벡터 반환 normal == unit
	const Vector3D_<T> unit()
	{
		return Vector3D_<T>(x / x, y / y, z / z);
	}

	float angle(const Vector3D_<T>& _v)
	{
		Vector3D_<T> a = unit();
		Vector3D_<T> b = _v.unit();
		float cosTheta = a.x * b.x + a.y * b.y + a.z * b.z; // 내적
		float degree = RadianToDegree(acos(cosTheta));
		return degree;
	}
};

template <typename T>
class Vector4D_
{
public:
	union
	{
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		T v[4];
	};

public:
	Vector4D_() : x(0), y(0), z(0), w(0) {};
	Vector4D_(const T& _x, const T& _y, const T& _z, const T& _w) : x(_x), y(_y), z(_z), w(_w) {};
	Vector4D_(const Point_<T>& _pos) : x(_pos.x), y(_pos.y), z(0), w(0) {};
	Vector4D_(const Point3D_<T>& _pos) : x(_pos.x), y(_pos.y), z(_pos.z), w(0) {};
	Vector4D_(const Vector2D_<T>& _v) : x(_v.x), y(_v.y), z(0), w(0) {};
	Vector4D_(const Vector3D_<T>& _v) : x(_v.x), y(_v.y), z(_v.z), w(0) {};
	Vector4D_(const Vector4D_<T>& _v) : x(_v.x), y(_v.y), z(_v.z), w(_v.w) {};
	~Vector4D_() {};

	Vector4D_<T> operator +(const Vector4D_<T>& _v)
	{
		return Vector4D_<T>(x + _v.x, y + _v.y, z + _v.z, w + _v.w);
	}

	Vector4D_<T> operator - (const Vector4D_<T>& _v)
	{
		return Vector4D_<T>(x - _v.x, y - _v.y, z - _v.z, w - _v.w);
	}

	Vector4D_<T> operator *(const T& _val)
	{
		return Vector4D_<T>(x * _val, y * _val, z * _val, w * _val);
	}

	Vector4D_<T> operator /(const T& _val)
	{
		return Vector4D_<T>(x / _val, y / _val, z / _val, w / _val);
	}

	void operator =(const Point_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = 0;
		w = 0;
	}

	void operator =(const Point3D_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = _v.z;
		w = 0;
	}

	void operator =(const Vector2D_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = 0;
		w = 0;
	}

	void operator =(const Vector3D_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = _v.z;
		w = 0;
	}

	void operator =(const Vector4D_<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = _v.z;
		w = _v.w;
	}

	void operator +=(const Vector4D_<T>& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
		w += _v.w;
	}

	void operator -=(const Vector4D_<T>& _v)
	{
		x -= _v.x;
		y -= _v.y;
		z -= _v.z;
		w -= _v.w;
	}

	void operator *=(const T& _val)
	{
		x *= _val;
		y *= _val;
		z *= _val;
		w *= _val;
	}

	void operator /=(const T& _val)
	{
		x /= _val;
		y /= _val;
		z /= _val;
		w /= _val;
	}

	bool operator ==(const Vector4D_<T>& _v)
	{
		if ((x == _v.x) && (y == _v.y) && (z == _v.z) && (w == _v.w))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Vector4D_<T>& _v)
	{
		if ((x != _v.x) || (y != _v.y) || (z != _v.z) || (w != _v.w))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <(const Vector4D_<T>& _v)
	{
		if ((x < _v.x) && (y < _v.y) && (z < _v.z) && (w < _v.w))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >(const Vector4D_<T>& _v)
	{
		if ((x > _v.x) && (y > _v.y) && (z > _v.z) && (w > _v.w))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <=(const Vector4D_<T>& _v)
	{
		if ((x <= _v.x) && (y <= _v.y) && (z <= _v.z) && (w <= _v.w))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >=(const Vector4D_<T>& _v)
	{
		if ((x >= _v.x) && (y >= _v.y) && (z >= _v.z) && (w >= _v.w))
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
		return sqrt(static_cast<float>(x * x + y * y + z * z + w * w));
	}
	// 정규화: 단위벡터(자신을) 계산
	void normalized()
	{
		this = unit();
	}
	// 단위벡터 반환 normal == unit
	const Vector4D_<T> unit()
	{
		return Vector4D_<T>(x / x, y / y, z / z, w / w);
	}

	float angle(const Vector4D_<T>& _v)
	{
		Vector4D_<T> a = unit();
		Vector4D_<T> b = _v.unit();
		float cosTheta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; // 내적
		float degree = RadianToDegree(acos(cosTheta));
		return degree;
	}
};

using Vector = Vector2D_<int>;
using Vector2D = Vector2D_<int>;
using Vector2f = Vector2D_<float>;
using Vector3D = Vector3D_<int>;
using Vector3f = Vector3D_<float>;
using Vector4D = Vector4D_<int>;
using Vector4f = Vector4D_<float>;