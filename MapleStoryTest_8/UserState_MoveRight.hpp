#pragma once
#include "UserState_Idle.hpp"
#include "Resource.h"

class UserState_MoveRight : public UserState
{
public:
	std::vector<std::wstring> textureKeyList;
	int walkState = 0;

	float beforeTime = 0.0f;
	float effectTime = 0.0f;

public:
	UserState_MoveRight(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};