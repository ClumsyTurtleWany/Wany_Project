#pragma once
#include "Scene.hpp"
#include "NPC.hpp"
#include "UIManager.hpp"
#include "UI_HPStatus.hpp"
#include "UI_Exit.hpp"
#include "UI_Exp.hpp"

class Scene_InGame : public Scene
{
public:
	Player* user;
	Map* currentMap;
	Camera* renderCamera;

	UI_HPStatus* HPStatus = nullptr;
	UI_Exp* uiExp = nullptr;
	UI_Exit* uiExit = nullptr;

	std::vector<UserInterface*>	uiList;

public:
	Scene_InGame(MapleStory* _game);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};