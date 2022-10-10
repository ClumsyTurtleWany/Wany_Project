#pragma once
#include "Scene.hpp"
#include "NPC.hpp"
#include "UIManager.hpp"
#include "UI_HPStatus.hpp"
#include "UI_Exit.hpp"
#include "UI_Exp.hpp"

class Scene_InGame : public Scene
{
private:
	Player* user;
	Map* currentMap;
	Camera* renderCamera;

	UI_HPStatus* HPStatus = nullptr;
	UI_Exp* uiExp = nullptr;
	UI_Exit* uiExit = nullptr;

	std::vector<UserInterface*>	uiList;

	int FPS = 0;
	float timeCounter = 0.0f;
	float beforeTime = 0.0f;

public:
	Scene_InGame(MapleStory* _game);

public:
	bool changeCurrentMap(std::wstring _name, Vector2f _pos);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};