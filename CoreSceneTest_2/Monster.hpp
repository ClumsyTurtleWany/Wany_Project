#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"

class UserState;

class Monster
{
public:
	object2D<float>* pObj;

	enum class Direction
	{
		Left,
		Right
	};

	Direction currentDirection;

	SpaceDivision* currentMap;

public:
	Monster();
	Monster(const Rect2f& _rect);
	virtual ~Monster();

public:
	virtual bool initialize();
	virtual bool frame(float _dt);
	virtual bool render();
	virtual bool release();

//public:
//	template <typename T>
//	void changeCurrentState();
};

//template <typename T>
//void Monster::changeCurrentState()
//{
//	delete currentState;
//	currentState = nullptr;
//	currentState = new T(this);
//}