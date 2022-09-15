#pragma once
#include "QuadTree.hpp"
#include "Player.hpp"
#include "Timer.hpp"
#include "DXTextureManager.hpp"
#include "Resource.h"
#include "Monster.hpp"

class Scene
{
public:
	ID3D11Device*			m_pd3dDevice = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;

public:
	Player* user;
	SpaceDivision* worldMap;

	std::vector<Monster*>	MonsterList;
	std::vector<objectBase*>	NPCList;

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
		
public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};