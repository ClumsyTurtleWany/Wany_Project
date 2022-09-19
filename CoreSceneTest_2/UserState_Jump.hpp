#pragma once
#include "UserState_Idle.hpp"
#include "Resource.h"

class UserState_Jump : public UserState
{
public:
	std::vector<std::wstring> textureKeyList;
	int jumpState = 0;

	float beforeTime = 0.0f;

public:
	UserState_Jump(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};