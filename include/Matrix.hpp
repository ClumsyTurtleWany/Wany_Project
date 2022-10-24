#pragma once
#include <math.h>
#include <vector>

struct float3x3
{
	union
	{
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float arry[3][3];
	};
};

class Matrix3x3 : public float3x3
{
public:
	Matrix3x3() { clear(); };

public:
	void clear()
	{
		_11 = _12 = _13 = 0.0f;
		_21 = _22 = _23 = 0.0f;
		_31 = _32 = _33 = 0.0f;
	}

	void Identity()
	{
		clear();
		_11 = _22 = _33 = 1.0f;
	}

	Matrix3x3 Transpose()
	{
		Matrix3x3 rst;
		rst._11 = _11; rst._12 = _21; rst._13 = _31;
		rst._21 = _12; rst._22 = _22; rst._23 = _32;
		rst._31 = _13; rst._32 = _23; rst._33 = _33;
		return rst;
	}

public:
	void operator= (Matrix3x3& _mat)
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				arry[row][col] = _mat.arry[row][col];
			}
		}
	}

	Matrix3x3 operator* (Matrix3x3& _mat)
	{
		Matrix3x3 rst;
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				rst.arry[row][col] = arry[row][0] * _mat.arry[0][col] + arry[row][1] * _mat.arry[1][col] + arry[row][2] * _mat.arry[2][col];
			}
		}
		return rst;
	}
};

struct float4x4
{
	union
	{
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float arry[4][4];
	};
};

class Matrix4x4 : public float4x4
{
public:
	Matrix4x4() { clear(); };

public:
	void clear()
	{
		_11 = _12 = _13 = _14 = 0.0f;
		_21 = _22 = _23 = _24 = 0.0f;
		_31 = _32 = _33 = _34 = 0.0f;
		_41 = _42 = _43 = _44 = 0.0f;
	}

	void Identity()
	{
		clear();
		_11 = _22 = _33 = _44 = 1.0f;
	}

	Matrix4x4 Transpose()
	{
		Matrix4x4 rst;
		rst._11 = _11; rst._12 = _21; rst._13 = _31; rst._14 = _41;
		rst._21 = _12; rst._22 = _22; rst._23 = _32; rst._24 = _42;
		rst._31 = _13; rst._32 = _23; rst._33 = _33; rst._34 = _43;
		rst._41 = _14; rst._42 = _24; rst._43 = _34; rst._44 = _44;
		return rst;
	}

public:
	void operator= (const Matrix4x4& _mat)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				arry[row][col] = _mat.arry[row][col];
			}
		}
	}

	Matrix4x4 operator* (Matrix4x4& _mat)
	{
		Matrix4x4 rst;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				rst.arry[row][col] = arry[row][0] * _mat.arry[0][col] + arry[row][1] * _mat.arry[1][col] + arry[row][2] * _mat.arry[2][col] + arry[row][3] * _mat.arry[3][col];
			}
		}
		return rst;
	}

	Matrix4x4 operator* (const float& _val)
	{
		Matrix4x4 rst;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				rst.arry[row][col] = arry[row][col] * _val;
			}
		}
		return rst;
	}
};



inline Matrix3x3 Make2DMatrix_Scale(float _x, float _y)
{
	Matrix3x3 rst;
	rst.arry[0][0] = _x;
	rst.arry[1][1] = _y;
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix3x3 Make2DMatrix_Rotation(float _radian)
{
	Matrix3x3 rst;
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][1] = -sin(_radian);
	rst.arry[1][0] = sin(_radian);
	rst.arry[1][1] = cos(_radian);
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix3x3 Make2DMatrix_Translation(float _x, float _y)
{
	Matrix3x3 rst;
	rst.arry[2][0] = _x;
	rst.arry[2][1] = _y;
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix4x4 Make3DMatrix_Scale(float _x, float _y, float _z)
{
	Matrix4x4 rst;
	rst.arry[0][0] = _x;
	rst.arry[1][1] = _y;
	rst.arry[2][2] = _z;
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix4x4 Make3DMatrix_RotationX(float _radian)
{
	Matrix4x4 rst;
	rst.arry[0][0] = 1.0f;
	rst.arry[1][1] = cos(_radian);
	rst.arry[1][2] = -sin(_radian);
	rst.arry[2][1] = sin(_radian);
	rst.arry[2][2] = cos(_radian);
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix4x4 Make3DMatrix_RotationY(float _radian)
{
	Matrix4x4 rst;
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][2] = sin(_radian);
	rst.arry[1][1] = 1.0f;
	rst.arry[2][0] = -sin(_radian);
	rst.arry[2][2] = cos(_radian);
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix4x4 Make3DMatrix_RotationZ(float _radian)
{
	Matrix4x4 rst;
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][1] = -sin(_radian);
	rst.arry[1][0] = sin(_radian);
	rst.arry[1][1] = cos(_radian);
	rst.arry[2][2] = 1.0f;
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix4x4 Make3DMatrix_Translation(float _x, float _y, float _z)
{
	Matrix4x4 rst;
	rst.arry[0][0] = 1.0f;
	rst.arry[1][1] = 1.0f;
	rst.arry[2][2] = 1.0f;

	rst.arry[3][0] = _x;
	rst.arry[3][1] = _y;
	rst.arry[3][2] = _z;
	rst.arry[3][3] = 1.0f;

	return rst;
}