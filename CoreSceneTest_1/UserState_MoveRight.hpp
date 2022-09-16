#pragma once
#include "UserState_Idle.hpp"
#include "Resource.h"

class UserState_MoveRight : public UserState
{
public:
	UserState_MoveRight(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};