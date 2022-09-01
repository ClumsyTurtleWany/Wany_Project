#pragma once
#include <iostream>
#include <windows.h>
#include "QuadTree.hpp"
#include "Octree.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "Define.hpp"
#include "DXTextureManager.hpp"

enum class CORE_TYPE
{
	GAME_2D,
	GAME_3D
};

class Core
{
public:
	//SpaceDivision<Shape, ObjectDimension>* map = nullptr;
	SpaceDivision* map = nullptr;
	objectBase* user = nullptr;

	objectBase* NPC;
	objectBase* OBSTACLE;

public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

public:
	//DXTextureManager textureMgr;

private:
	std::vector<objectBase*> NPCList;
	std::vector<objectBase*> obstacleList;
	std::vector<objectBase*> renderList;

public:
	Core();
	~Core();
public:
	void initialize();
	void frame(float _dt);
	void render();
	void release();
	void run();

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
};

Core::Core()
{

}

Core::~Core()
{
	release();
}

void Core::initialize()
{
	srand(static_cast<unsigned int>(time(NULL)));

	DXTextureManager::getTextureMgr()->setDevice(m_pd3dDevice, m_pImmediateContext);
	DXTextureManager::getTextureMgr()->initialize();

	DXShaderManager::getShaderMgr()->setDevice(m_pd3dDevice, m_pImmediateContext);

	if (map == nullptr)
	{
		return;
	}

	if (user == nullptr)
	{
		user = map->newPlayer();
		user->Random();
		user->name = "Player";
		user->createShader();
		//user->setDevice(m_pd3dDevice, m_pImmediateContext);
		user->setTexture(DXTextureManager::getTextureMgr()->getTexture(Texture_Key::Player));
		//user->initialize();
	}

	for (int i = 0; i < 5; i++)
	{
		objectBase* obj = map->newNPC();
		obj->Random();
		obj->name = "NPC_" + std::to_string(i + 1);
		obj->createShader();
		//obj->setDevice(m_pd3dDevice, m_pImmediateContext);
		obj->setTexture(DXTextureManager::getTextureMgr()->getTexture(Texture_Key::Npc));
		//obj->initialize();
		map->addObject(obj);
		NPCList.push_back(obj);
	}

	for (int i = 0; i < 5; i++)
	{
		objectBase* obj = map->newObstacle();
		obj->Random();
		obj->name = "Obj" + std::to_string(i + 1);
		obj->createShader();
		//obj->setDevice(m_pd3dDevice, m_pImmediateContext);
		obj->setTexture(DXTextureManager::getTextureMgr()->getTexture(Texture_Key::Obstacle));
		//obj->initialize();
		map->addObject(obj);
		obstacleList.push_back(obj);
	}
}

void Core::frame(float _dt)
{
	if (map == nullptr)
	{
		return;
	}

	map->updateDynamicObject();

	for (auto it : NPCList)
	{
		map->checkBorder(it);
		it->frame(_dt);
	}

	for (auto it : obstacleList)
	{
		map->checkBorder(it);
		it->frame(_dt);
	}

	map->checkBorder(user);
	if (user != nullptr)
	{
		user->frame(_dt);
	}

	map->Collision(user, &renderList);
}

void Core::render()
{
	if (user != nullptr)
	{
		user->render();
	}

	/*for (auto it : NPCList)
	{
		it->render();
	}

	for (auto it : obstacleList)
	{
		it->render();
	}*/
	
	/*if (!renderList.empty())
	{
		for (auto it : renderList)
		{
			it->render();
		}
		renderList.clear();
	}*/
}

void Core::release()
{
	if (map != nullptr)
	{
		delete map;
		map = nullptr;
	}

	if (!NPCList.empty())
	{
		NPCList.clear();
	}

	if (!obstacleList.empty())
	{
		obstacleList.clear();
	}

	if (!renderList.empty())
	{
		renderList.clear();
	}

}

void Core::run()
{
	initialize();
	float delay = 100.0f;
	float globalTime = 0.0f;
	float endTime = 60.0f;
	while (globalTime < endTime)
	{
		frame(delay / 1000.0f);
		render();
		renderList.clear();
		Sleep(static_cast<DWORD>(delay));
		system("cls");
		globalTime += delay / 1000.0f;
	}

	release();
}

void Core::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}