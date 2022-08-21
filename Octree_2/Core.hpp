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

class CoreBase
{
public:
	virtual void initialize() = 0;
	virtual void frame(float _dt) = 0;
	virtual void render() = 0;
	virtual void release() = 0;
	virtual void run() = 0;
	virtual void* getMap() = 0;
};

template <class Shape, class ObjectDimension>
class Core : public CoreBase
{
public:
	SpaceDivision<Shape, ObjectDimension>* map = nullptr;
	Player<ObjectDimension>* user = nullptr;

private:
	std::vector<ObjectDimension*> NPCList;
	std::vector<ObjectDimension*> obstacleList;
	std::vector<ObjectDimension*> renderList;

public:
	Core();
	~Core();
public:
	void initialize() override;
	void frame(float _dt) override;
	void render() override;
	void release() override;
	void run() override;
	void* getMap() override
	{
		return map;
	}
};

template <class Shape, class ObjectDimension>
Core<Shape, ObjectDimension>::Core()
{

}

template <class Shape, class ObjectDimension>
Core<Shape, ObjectDimension>::~Core()
{
	release();
}

template <class Shape, class ObjectDimension>
void Core<Shape, ObjectDimension>::initialize()
{
	srand(static_cast<unsigned int>(time(NULL)));

	if (map == nullptr)
	{
		return;
	}

	for (int i = 0; i < 5; i++)
	{
		ObjectDimension* obj = map->newNPC();
		obj->Random();
		obj->name = "NPC_" + std::to_string(i + 1);
		map->addObject(obj);
		NPCList.push_back(obj);
	}

	for (int i = 0; i < 20; i++)
	{
		ObjectDimension* obj = map->newObstacle();
		obj->Random();
		obj->name = "Obj" + std::to_string(i + 1);
		map->addObject(obj);
		obstacleList.push_back(obj);
	}
}

template <class Shape, class ObjectDimension>
void createMap()
{

}

template <class Shape, class ObjectDimension>
void Core<Shape, ObjectDimension>::frame(float _dt)
{
	map->updateDynamicObject();

	for (auto it : NPCList)
	{
		map->checkBorder(it);
		it->frame(_dt);
	}

	map->checkBorder(user->getObject());
	user->frame(_dt);

	map->Collision(user->getObject(), &renderList);
}

template <class Shape, class ObjectDimension>
void Core<Shape, ObjectDimension>::render()
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

	user->getObject()->render();
	if (!renderList.empty())
	{
		for (auto it : renderList)
		{
			it->render();
		}
	}
}

template <class Shape, class ObjectDimension>
void Core<Shape, ObjectDimension>::release()
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

template <class Shape, class ObjectDimension>
void Core<Shape, ObjectDimension>::run()
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