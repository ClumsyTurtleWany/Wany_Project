#pragma once
#include "GameCore.hpp"
#include "Player.hpp"
#include "Resource.h"

//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public GameCore
{
public:
	Player* user;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};