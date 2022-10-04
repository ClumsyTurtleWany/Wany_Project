#pragma once
#include "Input.hpp"

class Player;

// Finite State Machine
class UserState
{
protected:
	Player* user;

public:
	UserState(Player* _user);
	virtual ~UserState();

public:
	virtual bool initialize() = 0;
	virtual bool frame() = 0;
	virtual bool render() = 0;
	virtual bool release() = 0;

};