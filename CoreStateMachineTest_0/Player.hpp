#pragma once
#include "Object.hpp"

class UserState;

class Player
{
private:
	UserState* currentState;

public:
	Player();
	virtual ~Player();

public:
	bool frame(float _dt);
	bool render();

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