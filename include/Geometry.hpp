#pragma once

#define PI (double)3.141592
#define DegreeToRadian(x) (double)(x * PI / 180.0f)
#define RadianToDegree(x) (double)(x * 180.0f / PI)

class Matrix
{
private:
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
	}
};

