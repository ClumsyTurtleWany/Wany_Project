#pragma once
#include "QuadTree.hpp"
#include "Player.hpp"
#include "Timer.hpp"
#include "DXTextureManager.hpp"
#include "Resource.h"
//#include "Monster.hpp"
#include "Map.hpp"
#include "Camera.hpp"
#include "Define.hpp"
#include "SkillManager.hpp"
#include "EffectManager.hpp"
#include "NPCManager.hpp"
#include "UIManager.hpp"

class MapleStory;

class Scene
{
protected:
	MapleStory* game;

public:
	ID3D11Device*			m_pd3dDevice = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;

public:
	Scene(MapleStory* _game);
	virtual ~Scene();
	
public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
		
public:
	virtual bool initialize() = 0;
	virtual bool frame() = 0;
	virtual bool render() = 0;
	virtual bool release() = 0;
};