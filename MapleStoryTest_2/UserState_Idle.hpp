#pragma once
#include "UserState.hpp"
#include "DXWriter.hpp"

class UserState_Idle : public UserState
{
public:
	std::vector<std::wstring> textureKeyList;
	int idleState = 0;

	float beforeTime = 0.0f;
	float effectTime = 0.0f;

public:
	UserState_Idle(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

public:
	bool moveLeft();
	bool moveRight();
};
