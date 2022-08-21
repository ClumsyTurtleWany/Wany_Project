#pragma once
#include "Core.hpp"
#include "QuadTree.hpp"
#include "Player2D.hpp"
#include "NPC2D.hpp"
#include "Obstacle2D.hpp"

using Map2D = QuadTree<float>;
using ObjectList2D = std::vector<object2D<float>*>;
class Core2D : public Core
{
private:
	//Map2D* worldMap;
	QuadTree<float>* worldMap = nullptr;
	Player2D* user = nullptr;
	ObjectList2D NPCList;
	ObjectList2D obstacleList;
	ObjectList2D renderList;

public:
	void initialize();
	void frame(float _dt);
	void render();
	void release();
	void run();
};

void Core2D::initialize()
{
	srand(static_cast<unsigned int>(time(NULL)));
	worldMap = new Map2D;
	worldMap->create(0, 0, 128, 128);

	user = new Player2D("User", Rect2f(50, 50, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	user->mass = 100.0f;
	user->force = Vector2f(200, 100);
	worldMap->addObject(user);

	NPC2D* npc1 = new NPC2D("NPC_1", Rect2f(60, 60, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc1->mass = 100.0f;
	npc1->force = Vector2f(100, 200);
	worldMap->addObject(npc1);
	NPCList.push_back(npc1);

	NPC2D* npc2 = new NPC2D("NPC_2", Rect2f(60, 60, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc2->mass = 200.0f;
	npc2->force = Vector2f(200, 200);
	worldMap->addObject(npc2);
	NPCList.push_back(npc2);

	NPC2D* npc3 = new NPC2D("NPC_3", Rect2f(60, 60, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	npc3->mass = 250.0f;
	npc3->force = Vector2f(500, 0);
	worldMap->addObject(npc3);
	NPCList.push_back(npc3);

	for (int i = 0; i < 10; i++)
	{
		Obstacle2D* obj = new Obstacle2D;
		obj->Random();
		obj->name = "Obj" + std::to_string(i + 1);
		worldMap->addObject(obj);
		obstacleList.push_back(obj);
	}
}

void Core2D::frame(float _dt)
{
	worldMap->updateDynamicObject();

	for (auto it : NPCList)
	{
		if (worldMap->isHitLeft(it) || worldMap->isHitRight(it))
		{
			it->force.x *= -1;
			it->velocity.x = 0;
		}
		if (worldMap->isHitTop(it) || worldMap->isHitBottom(it))
		{
			it->force.y *= -1;
			it->velocity.y = 0;
		}

		it->frame(_dt);
	}

	if (worldMap->isHitLeft(user) || worldMap->isHitRight(user))
	{
		user->force.x *= -1;
		user->velocity.x = 0;
	}
	if (worldMap->isHitTop(user) || worldMap->isHitBottom(user))
	{
		user->force.y *= -1;
		user->velocity.y = 0;
	}
	user->frame(_dt);

	worldMap->Collision(user, &renderList);
}

void Core2D::render()
{
	std::cout << "Player2D - ";
	std::cout << "L: " << user->rect.left() << ", ";
	std::cout << "T: " << user->rect.top() << ", ";
	std::cout << "R: " << user->rect.right() << ", ";
	std::cout << "B: " << user->rect.bottom() << std::endl;

	if (!renderList.empty())
	{
		for (auto it : renderList)
		{
			std::cout << "[ " << it->name << " ] - ";
			std::cout << "L: " << it->rect.left() << ", ";
			std::cout << "T: " << it->rect.top() << ", ";
			std::cout << "R: " << it->rect.right() << ", ";
			std::cout << "B: " << it->rect.bottom() << std::endl;
		}
	}
}

void Core2D::release()
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

void Core2D::run()
{
	initialize();
	float delay = 100.0f;
	float globalTime = 0.0f;
	while (globalTime < 60.0f)
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