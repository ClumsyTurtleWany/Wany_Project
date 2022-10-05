#pragma once
#include "Scene.hpp"
#include "NPC.hpp"

class Scene_InGame : public Scene
{
public:
	Player* user;
	Map* currentMap;
	Camera* renderCamera;

	std::vector<NPC*>	NPCList;
	std::vector<UserInterface*>	uiList;

public:
	Scene_InGame(MapleStory* _game);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};