#pragma once
#include "Resource.h"
#include "Define.hpp"
#include "FMODSoundManager.hpp"

//#include "Map.hpp"
//#include "Camera.hpp"
//#include "SkillManager.hpp"
//#include "EffectManager.hpp"
//#include "NPCManager.hpp"
//#include "UIManager.hpp"
//#include "QuadTree.hpp"
//#include "Player.hpp"
//#include "Timer.hpp"
//#include "DXTextureManager.hpp"

class MapleStory;

class Scene
{
protected:
	MapleStory* game;

public:
	Scene(MapleStory* _game);
	virtual ~Scene();
		
public:
	virtual bool initialize() = 0;
	virtual bool frame() = 0;
	virtual bool render() = 0;
	virtual bool release() = 0;
};