#pragma once

#include "Core.hpp"

using Map3D = Octree<float>;
using ObjectList3D = std::vector<Object*>;
class Core3D : public Core
{
private:
	Map3D* worldMap = nullptr;
	Player3D* user = nullptr;
	ObjectList3D NPCList;
	ObjectList3D obstacleList;
	ObjectList3D renderList;

public:
	Core3D();
	~Core3D();

public:
	void initialize();
	void frame(float _dt);
	void render();
	void release();
	void run();
};

Core3D::Core3D()
{

}

Core3D::~Core3D()
{
	release();
}

void Core3D::initialize()
{
	srand(static_cast<unsigned int>(time(NULL)));
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
	}
}

void Core3D::frame(float _dt)
{
	worldMap->updateDynamicObject();

	for (auto it : NPCList)
	{
		if (worldMap->isHitMinX(it) || worldMap->isHitMaxX(it))
		{
			it->force.dx *= -1;
			it->velocity.dx = 0;
		}
		if (worldMap->isHitMinY(it) || worldMap->isHitMaxY(it))
		{
			it->force.dy *= -1;
			it->velocity.dy = 0;
		}
		if (worldMap->isHitMinZ(it) || worldMap->isHitMaxZ(it))
		{
			it->force.dz *= -1;
			it->velocity.dz = 0;
		}

		it->frame(_dt);
	}

	if (worldMap->isHitMinX(user) || worldMap->isHitMaxX(user))
	{
		user->force.dx *= -1;
		user->velocity.dx = 0;
	}
	if (worldMap->isHitMinY(user) || worldMap->isHitMaxY(user))
	{
		user->force.dy *= -1;
		user->velocity.dy = 0;
	}
	if (worldMap->isHitMinZ(user) || worldMap->isHitMaxZ(user))
	{
		user->force.dz *= -1;
		user->velocity.dz = 0;
	}
	user->frame(_dt);

	worldMap->Collision(user, &renderList);
}

void Core3D::render()
{
	std::cout << "Player3D - ";
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
	}
}

void Core3D::release()
{
	if (worldMap != nullptr)
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
	}
}

void Core3D::run()
{
	initialize();
	float delay = 100.0f;
	float globalTime = 0.0f;
	float endTime = 1.0f;
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