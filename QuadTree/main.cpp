#include <iostream>
#include "QuadTree.hpp"
#include "Vector.hpp"

int main()
{
	QuadTree quadTree;
	quadTree.create(0, 0, 128, 128);

	object player(Rect(50, 50, 20, 20), OBJECT_TYPE::DYNAMIC_OBJECT);
	quadTree.addObject(&player);

	for (int i = 0; i < 100; i++)
	{
		object* obj = new object;
		obj->Random();
		quadTree.addObject(obj);
	}

	object player2(Rect(60, 60, 20, 20), OBJECT_TYPE::DYNAMIC_OBJECT);
	quadTree.addObject(&player2);
	
	std::vector<object*> collisionObject;
	std::vector<Rect> intersectionArea;
	if (quadTree.Collision(&player, &collisionObject, &intersectionArea))
	{
		if (!collisionObject.empty())
		{
			for (auto it : collisionObject)
			{
				std::cout << "Collision Object" << std::endl;
				std::cout << "left: " << it->rect.left() << std::endl;
				std::cout << "top: " << it->rect.top() << std::endl;
				std::cout << "right: " << it->rect.right() << std::endl;
				std::cout << "bottom: " << it->rect.bottom() << std::endl;
			}
		}
	}

	Vector2D_<int> v1;

	return 0;
}