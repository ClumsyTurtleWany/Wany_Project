#pragma once
#include "Point.hpp"

template <typename T>
class Cube
{
public:
	Point3D_<T> pos;
	T size = 0;
	float theta = 0.0f;
	float pi = 0.0f;

public:
	Cube() {};
	~Cube() {};



};