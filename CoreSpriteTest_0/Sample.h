#pragma once
#include "GameCore.hpp"
#include "Skill.hpp"

#define BACKGROUND L"../../resource/KGCABK.bmp"
#define TESTPNG L"../../resource/back_dis.png"
//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public GameCore
{
public:
	FiniteStateMachine* state;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};