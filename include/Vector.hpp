#pragma once
#include "Point.hpp"
#include "Matrix.hpp"

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

	Vector2D_<T> operator *(Matrix3x3& _mat)
	{
		float rst_x = (x * _mat.arry[0][0]) + (y * _mat.arry[1][0]) + (1 * _mat.arry[2][0]);
		float rst_y = (x * _mat.arry[0][1]) + (y * _mat.arry[1][1]) + (1 * _mat.arry[2][1]);
		float rst_z = (x * _mat.arry[0][2]) + (y * _mat.arry[1][2]) + (1 * _mat.arry[2][2]);

		return Vector2D_<T>(rst_x, rst_y);
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

	Vector3D_<T> operator *(Matrix3x3& _mat)
	{
		Vector3D_<T> rst;
		rst.x = (x * _mat.arry[0][0]) + (y * _mat.arry[1][0]) + (z * _mat.arry[2][0]);
		rst.y = (x * _mat.arry[0][1]) + (y * _mat.arry[1][1]) + (z * _mat.arry[2][1]);
		rst.z = (x * _mat.arry[0][2]) + (y * _mat.arry[1][2]) + (z * _mat.arry[2][2]);

		return rst;
	}

	Vector3D_<T> operator *(Matrix4x4& _mat)
	{
		float rst_x = (x * _mat.arry[0][0]) + (y * _mat.arry[1][0]) + (z * _mat.arry[2][0]) + (1.0f * _mat.arry[3][0]);
		float rst_y = (x * _mat.arry[0][1]) + (y * _mat.arry[1][1]) + (z * _mat.arry[2][1]) + (1.0f * _mat.arry[3][1]);
		float rst_z = (x * _mat.arry[0][2]) + (y * _mat.arry[1][2]) + (z * _mat.arry[2][2]) + (1.0f * _mat.arry[3][2]);
		float rst_w = (x * _mat.arry[0][3]) + (y * _mat.arry[1][3]) + (z * _mat.arry[2][3]) + (1.0f * _mat.arry[3][3]);

		return Vector3D_<T>(rst_x, rst_y, rst_z);
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

	float dot(const Vector3D_<T>& _v)
	{
		return static_cast<float>(x * _v.x + y * _v.y + z * _v.z);
	}

	Vector3D_<T> cross(const Vector3D_<T>& _v)
	{
		return Vector3D_<T>((y * _v.z - z * _v.y), (z * _v.x - x * _v.z), (x * _v.y - y * _v.x));
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

	Vector4D_<T> operator *(const Matrix4x4& _mat)
	{
		Vector4D_<T> rst;
		rst.x = (x * _mat.arry[0][0]) + (y * _mat.arry[1][0]) + (z * _mat.arry[2][0]) + (w * _mat.arry[3][0]);
		rst.y = (x * _mat.arry[0][1]) + (y * _mat.arry[1][1]) + (z * _mat.arry[2][1]) + (w * _mat.arry[3][1]);
		rst.z = (x * _mat.arry[0][2]) + (y * _mat.arry[1][2]) + (z * _mat.arry[2][2]) + (w * _mat.arry[3][2]);
		rst.w = (x * _mat.arry[0][3]) + (y * _mat.arry[1][3]) + (z * _mat.arry[2][3]) + (w * _mat.arry[3][3]);

		return rst;
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

