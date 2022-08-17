#pragma once
#include <iostream>
#include <windows.h>
#include "Octree.hpp"
#include "QuadTree.hpp"
#include "Vector.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"

class Core
{
public:
	virtual void initialize() = 0;
	virtual void frame(float _dt) = 0;
	virtual void render() = 0;
	virtual void release() = 0;
	virtual void run() = 0;
};