#pragma once
#include "GameCore.hpp"
#include "World.hpp"
#include "Actor.h"

//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public GameCore
{
public:
	ECS::World* NewWorld = nullptr;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};