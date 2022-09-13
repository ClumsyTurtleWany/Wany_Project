#pragma once
#include "UserState.hpp"

class UserState_Idle : public UserState
{
public:
	UserState_Idle(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};
