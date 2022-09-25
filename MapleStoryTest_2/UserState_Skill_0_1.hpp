#pragma once
#include "DXShaderManager.hpp"
#include "UserState_Idle.hpp"
#include "Object.hpp"
#include "DXTextureManager.hpp"
#include "Timer.hpp"
#include "Resource.h"
#include "UserState_Skill_0_2.hpp"
#include "Skill.hpp"

class UserState_Skill_0_1 : public UserState
{
public:
	Skill* skill;
	int skillState = 0;
	float beforeTime = 0.0f;
	float timeCounter = 0.0f;
	float effectTime = 0.0f;
	float frameTime = 0.0f;
	std::vector<std::wstring> textureKeyList;

	bool isCancle = false;

public:
	UserState_Skill_0_1(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};