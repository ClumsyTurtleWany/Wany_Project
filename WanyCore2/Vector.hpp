#pragma once
#include "Matrix.hpp"

template <typename T>
class Vector3D
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
	Vector3D() : x(0), y(0), z(0) {};
	Vector3D(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {};
	Vector3D(const Vector3D<T>& _v) : x(_v.x), y(_v.y), z(_v.z) {};
	~Vector3D() {};

	Vector3D<T> operator +(const Vector3D<T>& _v)
	{
		return Vector3D<T>(x + _v.x, y + _v.y, z + _v.z);
	}

	Vector3D<T> operator - (const Vector3D<T>& _v)
	{
		return Vector3D<T>(x - _v.x, y - _v.y, z - _v.z);
	}

	Vector3D<T> operator *(const T& _val)
	{
		return Vector3D<T>(x * _val, y * _val, z * _val);
	}

	Vector3D<T> operator *(Matrix3x3& _mat)
	{
		Vector3D<T> rst;
		rst.x = (x * _mat.arry[0][0]) + (y * _mat.arry[1][0]) + (z * _mat.arry[2][0]);
		rst.y = (x * _mat.arry[0][1]) + (y * _mat.arry[1][1]) + (z * _mat.arry[2][1]);
		rst.z = (x * _mat.arry[0][2]) + (y * _mat.arry[1][2]) + (z * _mat.arry[2][2]);

		return rst;
	}

	Vector3D<T> operator *(Matrix4x4& _mat)
	{
		float rst_x = (x * _mat.arry[0][0]) + (y * _mat.arry[1][0]) + (z * _mat.arry[2][0]) + (1.0f * _mat.arry[3][0]);
		float rst_y = (x * _mat.arry[0][1]) + (y * _mat.arry[1][1]) + (z * _mat.arry[2][1]) + (1.0f * _mat.arry[3][1]);
		float rst_z = (x * _mat.arry[0][2]) + (y * _mat.arry[1][2]) + (z * _mat.arry[2][2]) + (1.0f * _mat.arry[3][2]);
		float rst_w = (x * _mat.arry[0][3]) + (y * _mat.arry[1][3]) + (z * _mat.arry[2][3]) + (1.0f * _mat.arry[3][3]);
		rst_x /= rst_w;
		rst_y /= rst_w;
		rst_z /= rst_w;

		return Vector3D<T>(rst_x, rst_y, rst_z);
	}

	Vector3D<T> operator /(const T& _val)
	{
		return Vector3D<T>(x / _val, y / _val, z / _val);
	}

	void operator +=(const Vector3D<T>& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
	}

	void operator -=(const Vector3D<T>& _v)
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

	bool operator ==(const Vector3D<T>& _v)
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

	bool operator !=(const Vector3D<T>& _v)
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

	bool operator <(const Vector3D<T>& _v)
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

	bool operator >(const Vector3D<T>& _v)
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

	bool operator <=(const Vector3D<T>& _v)
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

	bool operator >=(const Vector3D<T>& _v)
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
	Vector3D<T> normalized()
	{
		float size = length();
		Vector3D<T> rst;
		rst.x = x / size;
		rst.y = y / size;
		rst.z = z / size;
		return rst;
	}
	// 단위벡터 반환 normal == unit
	const Vector3D<T> unit()
	{
		return Vector3D<T>(x / x, y / y, z / z);
	}

	float angle(const Vector3D<T>& _v)
	{
		Vector3D<T> a = unit();
		Vector3D<T> b = _v.unit();
		float cosTheta = a.x * b.x + a.y * b.y + a.z * b.z; // 내적
		float degree = RadianToDegree(acos(cosTheta));
		return degree;
	}

	float dot(const Vector3D<T>& _v)
	{
		return static_cast<float>(x * _v.x + y * _v.y + z * _v.z);
	}

	Vector3D<T> cross(const Vector3D<T>& _v)
	{
		return Vector3D<T>((y * _v.z - z * _v.y), (z * _v.x - x * _v.z), (x * _v.y - y * _v.x));
	}
};

template <typename T>
class Vector4D
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
	Vector4D() : x(0), y(0), z(0), w(0) {};
	Vector4D(const T& _x, const T& _y, const T& _z, const T& _w) : x(_x), y(_y), z(_z), w(_w) {};
	Vector4D(const Vector3D<T>& _v) : x(_v.x), y(_v.y), z(_v.z), w(0) {};
	Vector4D(const Vector4D<T>& _v) : x(_v.x), y(_v.y), z(_v.z), w(_v.w) {};
	~Vector4D() {};

	Vector4D<T> operator +(const Vector4D<T>& _v)
	{
		return Vector4D<T>(x + _v.x, y + _v.y, z + _v.z, w + _v.w);
	}

	Vector4D<T> operator - (const Vector4D<T>& _v)
	{
		return Vector4D<T>(x - _v.x, y - _v.y, z - _v.z, w - _v.w);
	}

	Vector4D<T> operator *(const T& _val)
	{
		return Vector4D<T>(x * _val, y * _val, z * _val, w * _val);
	}

	Vector4D<T> operator *(const Matrix4x4& _mat)
	{
		Vector4D<T> rst;
		rst.x = (x * _mat.arry[0][0]) + (y * _mat.arry[1][0]) + (z * _mat.arry[2][0]) + (w * _mat.arry[3][0]);
		rst.y = (x * _mat.arry[0][1]) + (y * _mat.arry[1][1]) + (z * _mat.arry[2][1]) + (w * _mat.arry[3][1]);
		rst.z = (x * _mat.arry[0][2]) + (y * _mat.arry[1][2]) + (z * _mat.arry[2][2]) + (w * _mat.arry[3][2]);
		rst.w = (x * _mat.arry[0][3]) + (y * _mat.arry[1][3]) + (z * _mat.arry[2][3]) + (w * _mat.arry[3][3]);

		return rst;
	}

	Vector4D<T> operator /(const T& _val)
	{
		return Vector4D<T>(x / _val, y / _val, z / _val, w / _val);
	}

	void operator =(const Vector3D<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = _v.z;
		w = 0;
	}

	void operator =(const Vector4D<T>& _v)
	{
		x = _v.x;
		y = _v.y;
		z = _v.z;
		w = _v.w;
	}

	void operator +=(const Vector4D<T>& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
		w += _v.w;
	}

	void operator -=(const Vector4D<T>& _v)
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

	bool operator ==(const Vector4D<T>& _v)
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

	bool operator !=(const Vector4D<T>& _v)
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

	bool operator <(const Vector4D<T>& _v)
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

	bool operator >(const Vector4D<T>& _v)
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

	bool operator <=(const Vector4D<T>& _v)
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

	bool operator >=(const Vector4D<T>& _v)
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
	const Vector4D<T> unit()
	{
		return Vector4D<T>(x / x, y / y, z / z, w / w);
	}

	float angle(const Vector4D<T>& _v)
	{
		Vector4D<T> a = unit();
		Vector4D<T> b = _v.unit();
		float cosTheta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; // 내적
		float degree = RadianToDegree(acos(cosTheta));
		return degree;
	}
};

using Vector3f = Vector3D<float>;
using Vector4f = Vector4D<float>;

