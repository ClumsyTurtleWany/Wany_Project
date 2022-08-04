#include "main.h"
#include <string>
#include <set>

void main()
{
	TREE::RBT<int, std::string> binTree;

	binTree.insert(9, "9");
	binTree.insert(7, "7");
	binTree.insert(8, "8");
	binTree.insert(6, "6");
	binTree.insert(4, "4");
	binTree.insert(5, "5");
	binTree.insert(2, "2");
	binTree.insert(3, "3");
	binTree.insert(10, "10");
	binTree.insert(11, "11");
	binTree.insert(13, "13");
	binTree.insert(12, "12");

	std::cout << "Size: " << binTree.size() << std::endl;
	for (auto it = binTree.begin(); it != binTree.end(); it++)
	{
		std::cout << "Key: " << (&it)->key << ", Data: " << (&it)->data << std::endl;
	}

	binTree.erase(8);
	std::cout << "after erase " << std::endl;
	std::cout << "Size: " << binTree.size() << std::endl;
	for (auto it = binTree.begin(); it != binTree.end(); it++)
	{
		std::cout << "Key: " << (&it)->key << ", Data: " << (&it)->data << std::endl;
	}
}