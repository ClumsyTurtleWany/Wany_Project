#pragma once
#include <iostream>
#include <windows.h>
#include "QuadTree.hpp"
#include "Octree.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "Define.hpp"

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

	if (map == nullptr)
	{
		return;
	}

	if (user == nullptr)
	{
		user = map->newPlayer();
		user->Random();
		user->name = "Player";
		user->setDevice(m_pd3dDevice, m_pImmediateContext);
		user->initialize();
	}

	for (int i = 0; i < 5; i++)
	{
		objectBase* obj = map->newNPC();
		obj->Random();
		obj->name = "NPC_" + std::to_string(i + 1);
		obj->setDevice(m_pd3dDevice, m_pImmediateContext);
		obj->initialize();
		map->addObject(obj);
		NPCList.push_back(obj);
	}

	for (int i = 0; i < 5; i++)
	{
		objectBase* obj = map->newObstacle();
		obj->Random();
		obj->name = "Obj" + std::to_string(i + 1);
		obj->setDevice(m_pd3dDevice, m_pImmediateContext);
		obj->initialize();
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
		it->frame(_dt);
		map->checkBorder(it);
	}

	for (auto it : obstacleList)
	{
		it->frame(_dt);
		map->checkBorder(it);
	}

	if (user != nullptr)
	{
		user->frame(_dt);
	}
	map->checkBorder(user);

	map->Collision(user, &renderList);
}

void Core::render()
{
	/*std::cout << "Player3D - ";
	std::cout << "Pos[x]: " << user->box.pos.x << ", ";
	std::cout << "Pos[y]: " << user->box.pos.y << ", ";
	std::cout << "Pos[z]: " << user->box.pos.z << ", ";
	std::cout << "width: " << user->box.width << ", ";
	std::cout << "height: " << user->box.height << ", ";
	std::cout << "depth: " << user->box.depth << std::endl;

	if (!renderList.empty())
	{
		for (auto it : renderList)
		{
			std::cout << "[ " << it->name << " ] - ";
			std::cout << "Pos[x]: " << it->box.pos.x << ", ";
			std::cout << "Pos[y]: " << it->box.pos.y << ", ";
			std::cout << "Pos[z]: " << it->box.pos.z << ", ";
			std::cout << "width: " << it->box.width << ", ";
			std::cout << "height: " << it->box.height << ", ";
			std::cout << "depth: " << it->box.depth << std::endl;
		}
	}*/

	if (user != nullptr)
	{
		user->render();
	}
	
	if (!renderList.empty())
	{
		for (auto it : renderList)
		{
			it->render();
		}
		renderList.clear();
	}
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