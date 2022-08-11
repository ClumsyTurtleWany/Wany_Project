#include <iostream>
#include "QuadTree.hpp"
#include "Vector.hpp"
#include <windows.h>

int main()
{
	srand(time(NULL));
	QuadTree quadTree;
	quadTree.create(0, 0, 128, 128);
	
	object* player = new object(Rect(50, 50, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	player->name = "P1";
	quadTree.addObject(player);
	
	object* player2 = new object(Rect(60, 60, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	player2->name = "P2";
	quadTree.addObject(player2);

	object* player3 = new object(Rect(30, 30, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	player3->name = "P3";
	quadTree.addObject(player3);

	object* player4 = new object(Rect(0, 0, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	player4->name = "P4";
	quadTree.addObject(player4);

	object* player5 = new object(Rect(80, 80, 30, 30), OBJECT_TYPE::DYNAMIC_OBJECT);
	player5->name = "P5";
	quadTree.addObject(player5);

	ObjectList dynamicObjectList;
	dynamicObjectList.push_back(player);
	dynamicObjectList.push_back(player2);
	dynamicObjectList.push_back(player3);
	dynamicObjectList.push_back(player4);
	dynamicObjectList.push_back(player5);

	for (auto it : dynamicObjectList)
	{		
		Vector velocity;
		velocity.x = rand() % 5 + 1;
		velocity.y = rand() % 5 + 1;
		velocity.x = rand() % 2 == 1 ? velocity.x *= -1 : velocity.x;
		velocity.y = rand() % 2 == 1 ? velocity.y *= -1 : velocity.y;
		it->direction = velocity;
	}

	ObjectList staticObjectList;
	for (int i = 0; i < 20; i++)
	{
		object* obj = new object;
		obj->Random();
		obj->name = "S" + std::to_string(i + 1);
		quadTree.addObject(obj);
		staticObjectList.push_back(obj);
	}

	while (1)
	{
		quadTree.updateDynamicObject();

		std::cout << "Player - ";
		std::cout << "L: " << player->rect.left() << ", ";
		std::cout << "T: " << player->rect.top() << ", ";
		std::cout << "R: " << player->rect.right() << ", ";
		std::cout << "B: " << player->rect.bottom() << std::endl;

		std::vector<object*> collisionObject;
		std::vector<Rect> intersectionArea;
		if (quadTree.Collision(player, &collisionObject, &intersectionArea))
		{
			if (!collisionObject.empty())
			{
				for (auto it : collisionObject)
				{
					std::cout << "Collision Object - ";
					if (!it->name.empty())
					{
						std::cout << "[ " << it->name << " ] - ";
						if (it->name == "P4" || it->name == "P5")
						{
							int a = 0;
						}

					}
					std::cout << "L: " << it->rect.left() << ", ";
					std::cout << "T: " << it->rect.top() << ", ";
					std::cout << "R: " << it->rect.right() << ", ";
					std::cout << "B: " << it->rect.bottom() << std::endl;
				}
			}
		}

		for (auto it : dynamicObjectList)
		{
			if (quadTree.isHitBoundary(it))
			{
				it->direction.x *= -1;
				it->direction.y *= -1;
			}
			it->move();
		}

		Sleep(200);
		system("cls");
	}

	Vector v1(10, 0);
	Vector v2(0, 10);
	player->direction = v2;
	Vector v3 = v1 + player->direction * 2;


	return 0;
}