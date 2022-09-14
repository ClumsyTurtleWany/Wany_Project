#pragma once
#include "Object.hpp"

class UserState;

class Player
{
protected:
	UserState* currentState;

public:
	object2D<float>* pObj;
	
	enum class Direction
	{
		Left,
		Right
	};

	Direction currentDirection;

public:
	Player();
	Player(const Rect2f& _rect);
	virtual ~Player();

public:
	virtual bool initialize();
	virtual bool frame(float _dt);
	virtual bool render();
	virtual bool release();

public:
	template <typename T>
	void changeCurrentState();
};

template <typename T>
void Player::changeCurrentState()
{
	delete currentState;
	currentState = nullptr;
	currentState = new T(this);
}