#pragma once
#include "UserState_Idle.hpp"
#include "Resource.h"

class UserState_MoveLeft : public UserState
{
public:
	UserState_MoveLeft(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};