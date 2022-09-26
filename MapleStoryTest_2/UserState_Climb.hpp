#pragma once
#include "UserState_Idle.hpp"
#include "Resource.h"

class UserState_Climb : public UserState
{
public:
	std::vector<std::wstring> textureKeyList;
	int state = 0;

	float beforeTime = 0.0f;
	float timeCounter = 0.0f;

public:
	UserState_Climb(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};