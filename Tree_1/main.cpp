#include "main.h"
#include <string>
#include <set>

void main()
{
	TREE::RBT<int, std::string> binTree;

	binTree.insert(25, "1");
	binTree.insert(7, "2");
	binTree.insert(3, "3");
	binTree.insert(2, "4");
	binTree.insert(5, "5");
	//binTree.insert(9, "6");
	//binTree.insert(8, "7");
	//binTree.insert(10, "8");
	binTree.insert(6, "9");
	//binTree.insert(16, "10");
	//binTree.insert(13, "11");
	binTree.insert(1, "12");
	//binTree.insert(22, "13");
	binTree.insert(32, "14");
	binTree.insert(56, "15");
	

	/*binTree.insert(4, "root");
	binTree.insert(2, "root-child[0]");
	binTree.insert(3, "root-child[0]-child[1]");*/

	//     4
	//    /
	//   2
	//    \
	//     3

	//binTree.erase(3);

	std::cout << "Size: " << binTree.size() << std::endl;
	for (auto it = binTree.begin(); it != binTree.end(); it++)
	{
		std::cout << "Key: " << (&it)->key << ", Data: " << (&it)->data << std::endl;
	}

	binTree.erase(7);
	std::cout << "after erase " << std::endl;
	std::cout << "Size: " << binTree.size() << std::endl;
	for (auto it = binTree.begin(); it != binTree.end(); it++)
	{
		std::cout << "Key: " << (&it)->key << ", Data: " << (&it)->data << std::endl;
	}
}