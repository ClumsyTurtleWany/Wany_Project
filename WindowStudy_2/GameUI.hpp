#pragma once
#include "WindowUI.hpp"
#include "Engine.hpp"

class GameUI : public WindowUI
{
private:
	Core* core;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};

bool GameUI::initialize()
{
	Engine* engine = Engine::getEngine(CORE_TYPE::GAME_3D);
	if (engine != nullptr)
	{
		core = engine->getCore();
	}

	if (core != nullptr)
	{
		core->initialize();
		return true;
	}
	else
	{
		return false;
	}
}
bool GameUI::frame()
{
	float delay = 100.0f;
	core->frame(delay / 1000.0f);
	return true;
}
bool GameUI::render()
{
	core->render();
	return true;
}
bool GameUI::release()
{
	return true;
}