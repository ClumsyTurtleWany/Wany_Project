#pragma once
#include "UserState_Idle.hpp"
#include "Resource.h"

class UserState_Jump : public UserState
{
public:
	UserState_Jump(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};