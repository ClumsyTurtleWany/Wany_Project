#pragma once
#include <iostream>
#include <windows.h>
#include "QuadTree.hpp"
#include "Octree.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"

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
	}

	for (int i = 0; i < 5; i++)
	{
		objectBase* obj = map->newNPC();
		obj->Random();
		obj->name = "NPC_" + std::to_string(i + 1);
		map->addObject(obj);
		NPCList.push_back(obj);
	}

	for (int i = 0; i < 20; i++)
	{
		objectBase* obj = map->newObstacle();
		obj->Random();
		obj->name = "Obj" + std::to_string(i + 1);
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

	map->checkBorder(user);

	if (user != nullptr)
	{
		user->frame(_dt);
	}

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
	/*if (worldMap != nullptr)
	{
		delete worldMap;
		worldMap = nullptr;
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
	}*/
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
		Sleep(static_cast<DWORD>(delay));
		system("cls");
		globalTime += delay / 1000.0f;
	}

	release();
}