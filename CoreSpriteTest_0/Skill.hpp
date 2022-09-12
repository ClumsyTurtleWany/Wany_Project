#pragma once
#include "DXShaderManager.hpp"
#include "FiniteStateMachine.hpp"
#include "Object.hpp"
#include "DXTextureManager.hpp"
#include "Timer.hpp"


#define SKILL_0_0 L"../resource/MapleStory/Skill/Skill1/0_0.bmp"
#define SKILL_0_1 L"../resource/MapleStory/Skill/Skill1/0_1.bmp"
#define SKILL_0_2 L"../resource/MapleStory/Skill/Skill1/0_2.bmp"
#define SKILL_0_3 L"../resource/MapleStory/Skill/Skill1/0_3.bmp"
#define SKILL_0_4 L"../resource/MapleStory/Skill/Skill1/0_4.bmp"
#define SKILL_0_5 L"../resource/MapleStory/Skill/Skill1/0_5.bmp"
#define SKILL_0_6 L"../resource/MapleStory/Skill/Skill1/0_6.bmp"

#define SKILL_1_0 L"../resource/MapleStory/Skill/Skill1/1_0.bmp"
#define SKILL_1_1 L"../resource/MapleStory/Skill/Skill1/1_1.bmp"
#define SKILL_1_2 L"../resource/MapleStory/Skill/Skill1/1_2.bmp"
#define SKILL_1_3 L"../resource/MapleStory/Skill/Skill1/1_3.bmp"
#define SKILL_1_4 L"../resource/MapleStory/Skill/Skill1/1_4.bmp"
#define SKILL_1_5 L"../resource/MapleStory/Skill/Skill1/1_5.bmp"
#define SKILL_1_6 L"../resource/MapleStory/Skill/Skill1/1_6.bmp"

#define SKILL_2_0 L"../resource/MapleStory/Skill/Skill1/2_0.bmp"
#define SKILL_2_1 L"../resource/MapleStory/Skill/Skill1/2_1.bmp"
#define SKILL_2_2 L"../resource/MapleStory/Skill/Skill1/2_2.bmp"
#define SKILL_2_3 L"../resource/MapleStory/Skill/Skill1/2_3.bmp"
#define SKILL_2_4 L"../resource/MapleStory/Skill/Skill1/2_4.bmp"
#define SKILL_2_5 L"../resource/MapleStory/Skill/Skill1/2_5.bmp"
#define SKILL_2_6 L"../resource/MapleStory/Skill/Skill1/2_6.bmp"

class Skill : public FiniteStateMachine
{
public:
	objectBase* skill;
	int skillState = 0;
	float beforeFrameTime = 0.0f;
	float secondPerFrame = 0.0f;
	float frameTime = 0.0f;
	float delayTime = 45.0f / 1000.0f;
	int FPS = 0;

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};