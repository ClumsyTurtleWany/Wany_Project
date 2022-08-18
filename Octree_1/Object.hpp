#pragma once
#include "Rect.hpp"
#include "Cube.hpp"
#include "Vector.hpp"
#include "Circle.hpp"
#include <string>

enum class OBJECT_TYPE
{
	STATIC_OBJECT,
	DYNAMIC_OBJECT
};

class objectBase
{
public:
	std::string name;
	float mass = 0.0f;
	OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

public:
};