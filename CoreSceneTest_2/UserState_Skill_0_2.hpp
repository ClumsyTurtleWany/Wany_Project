#pragma once
#include "DXShaderManager.hpp"
#include "UserState_Idle.hpp"
#include "Object.hpp"
#include "DXTextureManager.hpp"
#include "Timer.hpp"
#include "Resource.h"
#include "UserState_Skill_0_3.hpp"
#include "Skill.hpp"

class UserState_Skill_0_2 : public UserState
{
public:
	Skill* skill;
	int skillState = 0;
	float beforeFrameTime = 0.0f;
	float secondPerFrame = 0.0f;
	float frameTime = 0.0f;
	float delayTime = 45.0f / 1000.0f;
	int FPS = 0;
	std::vector<std::wstring> textureKeyList;

	bool isCancle = false;

public:
	UserState_Skill_0_2(Player* _user);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};