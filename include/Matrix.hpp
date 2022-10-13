#pragma once
#include <math.h>

template <typename T>
class Matrix
{
private:
public:
	int row = 0; // y
	int column = 0; // x

public:
	T** arry = nullptr;

public:
	Matrix() {};
	Matrix(int _row, int _column, T _val = NULL) : row(_row), column(_column)
	{
		if (create())
		{
			clear(_val);
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
		if (arry != nullptr || row == 0 || column == 0)
		{
			return false;
		}

		arry = new T * [row];
		for (int i = 0; i < row; i++)
		{
			arry[i] = new T[column];
		}

		return true;
	}

	void clear(T _val = NULL)
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
		if (arry == nullptr)
		{
			return;
		}

		for (int i = 0; i < row; i++)
		{
			delete arry[i];
		}
		delete[] arry;
		arry = nullptr;
	}

	T& at(int _row, int _column)
	{
		return &arry[_row][_column];
	}

	bool isCreated()
	{
		if (arry == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Matrix<T> Transpose()
	{
		Matrix<T> mat(column, row);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				mat.arry[j][i] = arry[i][j];
			}
		}

		return mat;
	}

	Matrix<T> Identity()
	{
		Matrix<T> mat(row, column);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				if (i == j)
				{
					mat.arry[i][j] = static_cast<T>(1);
				}
				else
				{
					mat.arry[i][j] = static_cast<T>(0);
				}
			}
		}

		return mat;
	}

	const int Row() const { return row; }
	const int Col() const { return column; }

public:

	Matrix<T> operator =(const Matrix<T>& _src)
	{
		Matrix<T> rst(_src.Row(), _src.Col());
		
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				rst.arry[i][j] = _src.arry[i][j];
			}
		}
		
		return rst;
	}

	Matrix<T> operator *(const float& _val)
	{
		Matrix<T> rst(this);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				rst.arry[i][j] *= _val;
			}
		}

		return rst;
	}

	Matrix<T> operator *(const Matrix<T>& _src)
	{
		if (column != _src.Row())
		{
			return Matrix<T>();
		}
		 
		Matrix<T> rst(row, _src.Col());
		for (int i = 0; i < rst.Row(); i++)
		{
			for (int j = 0; j < rst.Col(); j++)
			{
				rst.arry[i][j] = 0;
				for (int k = 0; k < column; k++)
				{
					rst.arry[i][j] += arry[i][k] * _src.arry[k][i];
				}
			}
		}

		return rst;
	}

	Matrix<T> operator +(const Matrix<T>& _src)
	{
		if ((row != _src.Row()) || (column != _src.Col()))
		{
			return Matrix<T>();
		}

		Matrix<T> rst(this);
		for (int i = 0; i < rst.Row(); i++)
		{
			for (int j = 0; j < rst.Col(); j++)
			{
				rst.arry[i][j] = arry[i][j] + _src.arry[i][j];
			}
		}

		return rst;
	}

	Matrix<T> operator +(const T& _val)
	{
		if ((row == 0) || (column == 0))
		{
			return this;
		}

		Matrix<T> rst(this);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				rst.arry[i][j] += _val;
			}
		}

		return rst;
	}

	Matrix<T> operator -(const Matrix<T>& _src)
	{
		if ((row != _src.Row()) || (column != _src.Col()))
		{
			return Matrix<T>();
		}

		Matrix<T> rst(this);
		for (int i = 0; i < rst.Row(); i++)
		{
			for (int j = 0; j < rst.Col(); j++)
			{
				rst.arry[i][j] = arry[i][j] - _src.arry[i][j];
			}
		}

		return rst;
	}

	Matrix<T> operator -(const T& _val)
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

inline Matrix<float> Make2DMatrix_Scale(float _x, float _y)
{
	Matrix<float> rst(3, 3);
	rst.arry[0][0] = _x;
	rst.arry[1][1] = _y;
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix<float> Make2DMatrix_Rotation(float _radian)
{
	Matrix<float> rst(3, 3);
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][1] = -sin(_radian);
	rst.arry[1][0] = sin(_radian);
	rst.arry[1][1] = cos(_radian);
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix<float> Make2DMatrix_Translation(float _x, float _y)
{
	Matrix<float> rst(3, 3);
	rst.arry[2][0] = _x;
	rst.arry[2][1] = _y;
	rst.arry[2][2] = 1.0f;

	return rst;
}

inline Matrix<float> Make3DMatrix_Scale(float _x, float _y, float _z)
{
	Matrix<float> rst(4, 4);
	rst.arry[0][0] = _x;
	rst.arry[1][1] = _y;
	rst.arry[2][2] = _z;
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix<float> Make3DMatrix_RotationX(float _radian)
{
	Matrix<float> rst(4, 4);
	rst.arry[0][0] = 1.0f;
	rst.arry[1][1] = cos(_radian);
	rst.arry[1][2] = -sin(_radian);
	rst.arry[2][1] = sin(_radian);
	rst.arry[2][2] = cos(_radian);
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix<float> Make3DMatrix_RotationY(float _radian)
{
	Matrix<float> rst(4, 4);
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][2] = sin(_radian);
	rst.arry[1][1] = 1.0f;
	rst.arry[2][0] = -sin(_radian);
	rst.arry[2][2] = cos(_radian);
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix<float> Make3DMatrix_RotationZ(float _radian)
{
	Matrix<float> rst(4, 4);
	rst.arry[0][0] = cos(_radian);
	rst.arry[0][1] = -sin(_radian);
	rst.arry[1][0] = sin(_radian);
	rst.arry[1][1] = cos(_radian);
	rst.arry[2][2] = 1.0f;
	rst.arry[3][3] = 1.0f;

	return rst;
}

inline Matrix<float> Make3DMatrix_Translation(float _x, float _y, float _z)
{
	Matrix<float> rst(4, 4);
	rst.arry[3][0] = _x;
	rst.arry[3][1] = _y;
	rst.arry[3][2] = _z;
	rst.arry[3][3] = 1.0f;

	return rst;
}

