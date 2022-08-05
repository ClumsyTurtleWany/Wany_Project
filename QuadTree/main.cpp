#include <iostream>
#include "QuadTree.hpp"

int main()
{
	QuadTree quadTree;
	quadTree.create(0, 0, 100, 100);

	for (int i = 0; i < 10; i++)
	{
		object* obj = new object;
		obj->Random();
		quadTree.addObject(obj);
	}

	return 0;
}