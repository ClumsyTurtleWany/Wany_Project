#pragma once

#define PI (double)3.141592
#define DegreeToRadian(x) (double)(x * PI / 180.0f)
#define RadianToDegree(x) (double)(x * 180.0f / PI)

class Matrix
{
public:
	int x = 0;
	int y = 0;
	float** arry = nullptr;

public:
	Matrix() {};
	Matrix(int _x, int _y) : x(_x), y(_y)
	{
		arry = new float*[y];
		for (int i = 0; i < x; i++)
		{
			arry[i] = new float[x];
		}
	}
	~Matrix() {};

public:
	void release()
	{
		if (arry == nullptr)
		{
			return;
		}
		
		for (int i = 0; i < x; i++)
		{
			delete arry[i];
		}
		delete[] arry;
	}
};

void rotation2D(const Matrix& _src, Matrix& _dst, float _theta)
{
	// 2D rotation
	// cos(theta) -sin(theta)
	// sin(theta)  cos(theta)
	// x = _src.x * cos(theta) - _src.y * sin(theta)
	// y = _src.x * sin(theta) + _src.y * cos(theta)

	if (_src.y != 2)
	{
		return;
	}

	Matrix temp(1, 2);
	temp.arry[0][0] = _src.arry[0][0] * cos(_theta) - _src.arry[0][1] * sin(_theta);
	temp.arry[0][1] = _src.arry[0][0] * sin(_theta) + _src.arry[0][1] * cos(_theta);

	_dst.arry[0][0] = temp.arry[0][0];
	_dst.arry[0][1] = temp.arry[0][1];
}