#pragma once
#include <iostream>
#include <windows.h>
#include "Vector.hpp"

enum class CORE_TYPE
{
	GAME_2D,
	GAME_3D
};

class Core
{
public:
	virtual void initialize() = 0;
	virtual void frame(float _dt) = 0;
	virtual void render() = 0;
	virtual void release() = 0;
	virtual void run() = 0;
};