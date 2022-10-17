#pragma once

// WinAPI
#include <windows.h>
#pragma comment(lib, "winmm.lib") // timeGetTime

#include <cstdlib> // srand
#include <ctime> // time

extern class WindowUI* g_pWindow;

#define CoreMode
#define DEBUG_DISPLAY

// STL
#include <vector>
#include <string>
#include <map>
#include <filesystem> // c++ 17 std
//#include <fstream>

// Shape
#include "Vertex.hpp"
#include "Rect.hpp"
#include "Circle.hpp"
#include "Box.hpp"

// Design Pattern
template <class T>
class Singleton
{
private:
	static T* instance;

protected:
	Singleton() {};
	virtual ~Singleton()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

public:
	static T* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new T;
		}
		return instance;
	}
};

template <class T>
T* Singleton<T>::instance = nullptr;


//Matrix<float> Make2DMatrix_Scale(float _x, float _y)
//{
//	Matrix<float> rst(3, 3);
//	rst.arry[0][0] = _x;
//	rst.arry[1][1] = _y;
//	rst.arry[2][2] = 1.0f;
//
//	return rst;
//}
//
//Matrix<float> Make2DMatrix_Rotation(float _radian)
//{
//	Matrix<float> rst(3, 3);
//	rst.arry[0][0] = cos(_radian);
//	rst.arry[0][1] = -sin(_radian);
//	rst.arry[1][0] = sin(_radian);
//	rst.arry[1][1] = cos(_radian);
//	rst.arry[2][2] = 1.0f;
//
//	return rst;
//}
//
//Matrix<float> Make2DMatrix_Translation(float _x, float _y)
//{
//	Matrix<float> rst(3, 3);
//	rst.arry[2][0] = _x;
//	rst.arry[2][1] = _y;
//	rst.arry[2][2] = 1.0f;
//
//	return rst;
//}
//
//Matrix<float> Make3DMatrix_Scale(float _x, float _y, float _z)
//{
//	Matrix<float> rst(4, 4);
//	rst.arry[0][0] = _x;
//	rst.arry[1][1] = _y;
//	rst.arry[2][2] = _z;
//	rst.arry[3][3] = 1.0f;
//
//	return rst;
//}
//
//Matrix<float> Make3DMatrix_RotationX(float _radian)
//{
//	Matrix<float> rst(4, 4);
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
//Matrix<float> Make3DMatrix_RotationY(float _radian)
//{
//	Matrix<float> rst(4, 4);
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
//Matrix<float> Make3DMatrix_RotationZ(float _radian)
//{
//	Matrix<float> rst(4, 4);
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
//Matrix<float> Make3DMatrix_Translation(float _x, float _y, float _z)
//{
//	Matrix<float> rst(4, 4);
//	rst.arry[3][0] = _x;
//	rst.arry[3][1] = _y;
//	rst.arry[3][2] = _z;
//	rst.arry[3][3] = 1.0f;
//
//	return rst;
//}