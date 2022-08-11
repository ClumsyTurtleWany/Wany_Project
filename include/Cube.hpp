#pragma once
#include "Point.hpp"

class Cube
{
public:
	
	int width = 0;
	int depth = 0;
	int height = 0;

public:
	Cube() {};
	Cube(Point3D _pos, int _size) : c(_pos), width(_size), depth(_size), height(_size) {};
	Cube(Point3D _pos, int _width, int _depth, int _height) : c(_pos), width(_width), depth(_depth), height(_height) {};
	~Cube() {};



};