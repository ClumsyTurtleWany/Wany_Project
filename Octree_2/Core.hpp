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
	/*srand(static_cast<unsigned int>(time(NULL)));
	worldMap = new Map3D;
	worldMap->create(128.0f, 128.0f, 128.0f);

	user = new Player3D("User", Box(Point3f(50, 50, 50), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	user->mass = 100.0f;
	user->force = Vector3f(200, 100, 100);
	worldMap->addObject(user);

	NPC3D* npc1 = new NPC3D("NPC_1", Box(Point3f(60, 60, 60), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc1->mass = 100.0f;
	npc1->force = Vector3f(100, 200, 200);
	worldMap->addObject(npc1);
	NPCList.push_back(npc1);

	NPC3D* npc2 = new NPC3D("NPC_2", Box(Point3f(100, 100, 100), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc2->mass = 200.0f;
	npc2->force = Vector3f(200, 200, 0);
	worldMap->addObject(npc2);
	NPCList.push_back(npc2);

	NPC3D* npc3 = new NPC3D("NPC_3", Box(Point3f(10, 10, 10), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc3->mass = 250.0f;
	npc3->force = Vector3f(500, 0, 0);
	worldMap->addObject(npc3);
	NPCList.push_back(npc3);

	NPC3D* npc4 = new NPC3D("NPC_4", Box(Point3f(10, 50, 10), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc4->mass = 200.0f;
	npc4->force = Vector3f(0, 400, 0);
	worldMap->addObject(npc4);
	NPCList.push_back(npc4);

	for (int i = 0; i < 20; i++)
	{
		Obstacle3D* obj = new Obstacle3D;
		obj->Random();
		obj->name = "Obj" + std::to_string(i + 1);
		worldMap->addObject(obj);
		obstacleList.push_back(obj);
	}*/

	/*srand(static_cast<unsigned int>(time(NULL)));
	worldMap = new Map3D;
	worldMap->create(128.0f, 128.0f, 128.0f);*/


	/*NPC3D* npc1 = new NPC3D("NPC_1", Box(Point3f(60, 60, 60), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc1->mass = 100.0f;
	npc1->force = Vector3f(100, 200, 200);
	worldMap->addObject(npc1);
	NPCList.push_back(npc1);

	NPC3D* npc2 = new NPC3D("NPC_2", Box(Point3f(100, 100, 100), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc2->mass = 200.0f;
	npc2->force = Vector3f(200, 200, 0);
	worldMap->addObject(npc2);
	NPCList.push_back(npc2);

	NPC3D* npc3 = new NPC3D("NPC_3", Box(Point3f(10, 10, 10), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc3->mass = 250.0f;
	npc3->force = Vector3f(500, 0, 0);
	worldMap->addObject(npc3);
	NPCList.push_back(npc3);

	NPC3D* npc4 = new NPC3D("NPC_4", Box(Point3f(10, 50, 10), 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc4->mass = 200.0f;
	npc4->force = Vector3f(0, 400, 0);
	worldMap->addObject(npc4);
	NPCList.push_back(npc4);*/
	map->create()

	for (int i = 0; i < 20; i++)
	{
		Obstacle<ObjectDimension>* obj = new Obstacle3D;
		obj->Random();
		obj->name = "Obj" + std::to_string(i + 1);
		worldMap->addObject(obj);
		obstacleList.push_back(obj);
	}
}

template <class Shape, class ObjectDimension>
void Core<Shape, ObjectDimension>::frame(float _dt)
{
	/*worldMap->updateDynamicObject();

	for (auto it : NPCList)
	{
		if (worldMap->isHitMinX(it) || worldMap->isHitMaxX(it))
		{
			it->force.x *= -1;
			it->velocity.x = 0;
		}
		if (worldMap->isHitMinY(it) || worldMap->isHitMaxY(it))
		{
			it->force.y *= -1;
			it->velocity.y = 0;
		}
		if (worldMap->isHitMinZ(it) || worldMap->isHitMaxZ(it))
		{
			it->force.z *= -1;
			it->velocity.z = 0;
		}

		it->frame(_dt);
	}

	if (worldMap->isHitMinX(user) || worldMap->isHitMaxX(user))
	{
		user->force.x *= -1;
		user->velocity.x = 0;
	}
	if (worldMap->isHitMinY(user) || worldMap->isHitMaxY(user))
	{
		user->force.y *= -1;
		user->velocity.y = 0;
	}
	if (worldMap->isHitMinZ(user) || worldMap->isHitMaxZ(user))
	{
		user->force.z *= -1;
		user->velocity.z = 0;
	}
	user->frame(_dt);

	worldMap->Collision(user, &renderList);*/
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
	/*initialize();
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

	release();*/
}