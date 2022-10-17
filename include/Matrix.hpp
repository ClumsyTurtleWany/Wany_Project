#pragma once
#include <math.h>
#include <vector>

//class Matrix
//{
//private:
//public:
//	int row = 0; // y
//	int column = 0; // x
//
//public:
//	std::vector<std::vector<float>> arry;
//
//public:
//	Matrix() {};
//	Matrix(int _row, int _column, float _val = 0.0f) : row(_row), column(_column)
//	{
//		if (create())
//		{
//			set(_val);
//		}
//	}
//	Matrix(const Matrix* _src)
//	{
//		row = _src->Row();
//		column = _src->Col();
//		if (create())
//		{
//			for (int i = 0; i < row; i++)
//			{
//				for (int j = 0; j < column; j++)
//				{
//					arry[i][j] = _src->arry[i][j];
//				}
//			}
//		}
//
//	}
//
//	~Matrix() { release(); };
//
//public:
//	bool create()
//	{
//		if (!arry.empty() || row == 0 || column == 0)
//		{
//			return false;
//		}
//
//		arry.assign(row, std::vector<float>());
//		for (int idx = 0; idx < row; idx++)
//		{
//			arry[idx].assign(column, 0.0f);
//		}
//
//		return true;
//	}
//
//	void set(float _val = 0.0f)
//	{
//		for (int i = 0; i < row; i++)
//		{
//			for (int j = 0; j < column; j++)
//			{
//				arry[i][j] = _val;
//			}
//		}
//	}
//
//	void release()
//	{
//		arry.clear();
//	}
//
//	Matrix Transpose()
//	{
//		Matrix mat(column, row);
//
//		for (int i = 0; i < row; i++)
//		{
//			for (int j = 0; j < column; j++)
//			{
//				mat.arry[j][i] = arry[i][j];
//			}
//		}
//
//		return mat;
//	}
//
//	Matrix Identity()
//	{
//		Matrix mat(row, column);
//
//		for (int i = 0; i < row; i++)
//		{
//			for (int j = 0; j < column; j++)
//			{
//				if (i == j)
//				{
//					mat.arry[i][j] = 1.0f;
//				}
//				else
//				{
//					mat.arry[i][j] = 0.0f;
//				}
//			}
//		}
//
//		return mat;
//	}
//
//	const int Row() const { return row; }
//	const int Col() const { return column; }
//
//public:
//
//	void operator =(const Matrix& _src)
//	{
//		arry.clear();
//		row = _src.Row();
//		column = _src.Col();
//		if (create())
//		{
//			for (int i = 0; i < row; i++)
//			{
//				for (int j = 0; j < column; j++)
//				{
//					arry[i][j] = _src.arry[i][j];
//				}
//			}
//		}
//	}
//
//	Matrix operator *(const float& _val)
//	{
//		Matrix rst(this);
//		for (int i = 0; i < row; i++)
//		{
//			for (int j = 0; j < column; j++)
//			{
//				rst.arry[i][j] *= _val;
//			}
//		}
//
//		return rst;
//	}
//
//	Matrix operator *(const Matrix& _src)
//	{
//		if (column != _src.Row())
//		{
//			return Matrix();
//		}
//		 
//		Matrix rst(row, _src.Col());
//		for (int i = 0; i < rst.Row(); i++)
//		{
//			for (int j = 0; j < rst.Col(); j++)
//			{
//				rst.arry[i][j] = 0;
//				
//				for (int k = 0; k < rst.Col(); k++)
//				{
//					rst.arry[i][j] += arry[i][k] * _src.arry[k][j];
//				}
//			}
//		}
//
//		return rst;
//	}
//
//	Matrix operator +(const Matrix& _src)
//	{
//		if ((row != _src.Row()) || (column != _src.Col()))
//		{
//			return Matrix();
//		}
//
//		Matrix rst(this);
//		for (int i = 0; i < rst.Row(); i++)
//		{
//			for (int j = 0; j < rst.Col(); j++)
//			{
//				rst.arry[i][j] = arry[i][j] + _src.arry[i][j];
//			}
//		}
//
//		return rst;
//	}
//
//	Matrix operator +(const float& _val)
//	{
//		if ((row == 0) || (column == 0))
//		{
//			return this;
//		}
//
//		Matrix rst(this);
//		for (int i = 0; i < row; i++)
//		{
//			for (int j = 0; j < column; j++)
//			{
//				rst.arry[i][j] += _val;
//			}
//		}
//
//		return rst;
//	}
//
//	Matrix operator -(const Matrix& _src)
//	{
//		if ((row != _src.Row()) || (column != _src.Col()))
//		{
//			return Matrix();
//		}
//
//		Matrix rst(this);
//		for (int i = 0; i < rst.Row(); i++)
//		{
//			for (int j = 0; j < rst.Col(); j++)
//			{
//				rst.arry[i][j] = arry[i][j] - _src.arry[i][j];
//			}
//		}
//
//		return rst;
//	}
//
//	Matrix operator -(const float& _val)
//	{
//		if ((row == 0) || (column == 0))
//		{
//			return this;
//		}
//
//		Matrix rst(this);
//		for (int i = 0; i < row; i++)
//		{
//			for (int j = 0; j < column; j++)
//			{
//				rst.arry[i][j] -= _val;
//			}
//		}
//
//		return rst;
//	}	
//};
//
//inline Matrix Make2DMatrix_Scale(float _x, float _y)
//{
//	Matrix rst(3, 3);
//	rst.arry[0][0] = _x;
//	rst.arry[1][1] = _y;
//	rst.arry[2][2] = 1.0f;
//
//	return rst;
//}
//
//inline Matrix Make2DMatrix_Rotation(float _radian)
//{
//	Matrix rst(3, 3);
//	rst.arry[0][0] = cos(_radian);
//	rst.arry[0][1] = -sin(_radian);
//	rst.arry[1][0] = sin(_radian);
//	rst.arry[1][1] = cos(_radian);
//	rst.arry[2][2] = 1.0f;
//
//	return rst;
//}
//
//inline Matrix Make2DMatrix_Translation(float _x, float _y)
//{
//	Matrix rst(3, 3);
//	rst.arry[2][0] = _x;
//	rst.arry[2][1] = _y;
//	rst.arry[2][2] = 1.0f;
//
//	return rst;
//}
//
//inline Matrix Make3DMatrix_Scale(float _x, float _y, float _z)
//{
//	Matrix rst(4, 4);
//	rst.arry[0][0] = _x;
//	rst.arry[1][1] = _y;
//	rst.arry[2][2] = _z;
//	rst.arry[3][3] = 1.0f;
//
//	return rst;
//}
//
//inline Matrix Make3DMatrix_RotationX(float _radian)
//{
//	Matrix rst(4, 4);
//	rst.arry[0][0] = 1.0f;
//	rst.arry[1][1] = cos(_radian);
//	rst.arry[1][2] = -sin(_radian);
//	rst.arry[2][1] = sin(_radian);
//	rst.arry[2][2] = cos(_radian);
//	rst.arry[3][3] = 1.0f;
//
//	return rst;
//}
//
//inline Matrix Make3DMatrix_RotationY(float _radian)
//{
//	Matrix rst(4, 4);
//	rst.arry[0][0] = cos(_radian);
//	rst.arry[0][2] = sin(_radian);
//	rst.arry[1][1] = 1.0f;
//	rst.arry[2][0] = -sin(_radian);
//	rst.arry[2][2] = cos(_radian);
//	rst.arry[3][3] = 1.0f;
//
//	return rst;
//}
//
//inline Matrix Make3DMatrix_RotationZ(float _radian)
//{
//	Matrix rst(4, 4);
//	rst.arry[0][0] = cos(_radian);
//	rst.arry[0][1] = -sin(_radian);
//	rst.arry[1][0] = sin(_radian);
//	rst.arry[1][1] = cos(_radian);
//	rst.arry[2][2] = 1.0f;
//	rst.arry[3][3] = 1.0f;
//
//	return rst;
//}
//
//inline Matrix Make3DMatrix_Translation(float _x, float _y, float _z)
//{
//	Matrix rst(4, 4);
//	rst.arry[0][0] = 1.0f;
//	rst.arry[1][1] = 1.0f;
//	rst.arry[2][2] = 1.0f;
//	
//	rst.arry[3][0] = _x;
//	rst.arry[3][1] = _y;
//	rst.arry[3][2] = _z;
//	rst.arry[3][3] = 1.0f;
//
//	return rst;
//}

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
	void operator= (Matrix4x4& _mat)
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