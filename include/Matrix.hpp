#pragma once
#include <math.h>
#include <vector>

class Matrix
{
private:
public:
	int row = 0; // y
	int column = 0; // x

public:
	std::vector<std::vector<float>> arry;

public:
	Matrix() {};
	Matrix(int _row, int _column, float _val = 0.0f) : row(_row), column(_column)
	{
		if (create())
		{
			set(_val);
		}
	}
	Matrix(const Matrix* _src)
	{
		row = _src->Row();
		column = _src->Col();
		if (create())
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					arry[i][j] = _src->arry[i][j];
				}
			}
		}

	}

	~Matrix() { release(); };

public:
	bool create()
	{
		if (!arry.empty() || row == 0 || column == 0)
		{
			return false;
		}

		arry.assign(row, std::vector<float>());
		for (int idx = 0; idx < row; idx++)
		{
			arry[idx].assign(column, 0.0f);
		}

		return true;
	}

	void set(float _val = 0.0f)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				arry[i][j] = _val;
			}
		}
	}

	void release()
	{
		arry.clear();
	}

	Matrix Transpose()
	{
		Matrix mat(column, row);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				mat.arry[j][i] = arry[i][j];
			}
		}

		return mat;
	}

	Matrix Identity()
	{
		Matrix mat(row, column);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				if (i == j)
				{
					mat.arry[i][j] = 1.0f;
				}
				else
				{
					mat.arry[i][j] = 0.0f;
				}
			}
		}

		return mat;
	}

	const int Row() const { return row; }
	const int Col() const { return column; }

public:

	void operator =(const Matrix& _src)
	{
		arry.clear();
		row = _src.Row();
		column = _src.Col();
		if (create())
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					arry[i][j] = _src.arry[i][j];
				}
			}
		}
	}

	Matrix operator *(const float& _val)
	{
		Matrix rst(this);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				rst.arry[i][j] *= _val;
			}
		}

		return rst;
	}

	Matrix operator *(const Matrix& _src)
	{
		if (column != _src.Row())
		{
			return Matrix();
		}
		 
		Matrix rst(row, _src.Col());
		for (int i = 0; i < rst.Row(); i++)
		{
			for (int j = 0; j < rst.Col(); j++)
			{
				rst.arry[i][j] = 0;
				
				for (int k = 0; k < rst.Col(); k++)
				{
					rst.arry[i][j] += arry[i][k] * _src.arry[k][j];
				}
			}
		}

		return rst;
	}

	Matrix operator +(const Matrix& _src)
	{
		if ((row != _src.Row()) || (column != _src.Col()))
		{
			return Matrix();
		}

		Matrix rst(this);
		for (int i = 0; i < rst.Row(); i++)
		{
			for (int j = 0; j < rst.Col(); j++)
			{
				rst.arry[i][j] = arry[i][j] + _src.arry[i][j];
			}
		}

		return rst;
	}

	Matrix operator +(const float& _val)
	{
		if ((row == 0) || (column == 0))
		{
			return this;
		}

		Matrix rst(this);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				rst.arry[i][j] += _val;
			}
		}

		return rst;
	}

	Matrix operator -(const Matrix& _src)
	{
		if ((row != _src.Row()) || (column != _src.Col()))
		{
			return Matrix();
		}

		Matrix rst(this);
		for (int i = 0; i < rst.Row(); i++)
		{
			for (int j = 0; j < rst.Col(); j++)
			{
				rst.arry[i][j] = arry[i][j] - _src.arry[i][j];
			}
		}

		return rst;
	}

	Matrix operator -(const float& _val)
	{
		if ((row == 0) || (column == 0))
		{
			return this;
		}

		Matrix rst(this);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				rst.arry[i][j] -= _val;
			}
		}

		return rst;
	}	
};

inline Matrix Make2DMatrix_Scale(float _x, float _y)
{
	Matrix rst(3, 3);
	rst.arry[0][0] = _x;
	rst.arry[1][1] = _y;
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix Make2DMatrix_Rotation(float _radian)
{
	Matrix rst(3, 3);
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][1] = -sin(_radian);
	rst.arry[1][0] = sin(_radian);
	rst.arry[1][1] = cos(_radian);
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix Make2DMatrix_Translation(float _x, float _y)
{
	Matrix rst(3, 3);
	rst.arry[2][0] = _x;
	rst.arry[2][1] = _y;
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix Make3DMatrix_Scale(float _x, float _y, float _z)
{
	Matrix rst(4, 4);
	rst.arry[0][0] = _x;
	rst.arry[1][1] = _y;
	rst.arry[2][2] = _z;
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix Make3DMatrix_RotationX(float _radian)
{
	Matrix rst(4, 4);
	rst.arry[0][0] = 1.0f;
	rst.arry[1][1] = cos(_radian);
	rst.arry[1][2] = -sin(_radian);
	rst.arry[2][1] = sin(_radian);
	rst.arry[2][2] = cos(_radian);
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix Make3DMatrix_RotationY(float _radian)
{
	Matrix rst(4, 4);
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][2] = sin(_radian);
	rst.arry[1][1] = 1.0f;
	rst.arry[2][0] = -sin(_radian);
	rst.arry[2][2] = cos(_radian);
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix Make3DMatrix_RotationZ(float _radian)
{
	Matrix rst(4, 4);
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][1] = -sin(_radian);
	rst.arry[1][0] = sin(_radian);
	rst.arry[1][1] = cos(_radian);
	rst.arry[2][2] = 1.0f;
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix Make3DMatrix_Translation(float _x, float _y, float _z)
{
	Matrix rst(4, 4);
	rst.arry[0][0] = 1.0f;
	rst.arry[1][1] = 1.0f;
	rst.arry[2][2] = 1.0f;
	
	rst.arry[3][0] = _x;
	rst.arry[3][1] = _y;
	rst.arry[3][2] = _z;
	rst.arry[3][3] = 1.0f;

	return rst;
}

