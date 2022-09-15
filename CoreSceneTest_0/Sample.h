#pragma once
#include "GameCore.hpp"
#include "Player.hpp"
#include "Resource.h"
#include "Scene_Map_0.hpp"

//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public GameCore
{
public:
	//Player* user;
	Scene* currentScene = nullptr;
	Scene_Map_0* Scene_Map0 = nullptr;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};