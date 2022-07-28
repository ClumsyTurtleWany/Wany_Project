#include "main.h"
#include <set>

void main()
{
	TREE::Tree<int> binTree;

	binTree.insert(7);
	binTree.insert(3);
	binTree.insert(2);
	binTree.insert(5);
	binTree.insert(9);
	binTree.insert(8);
	binTree.insert(10);
	binTree.insert(6);

	auto it = binTree.find(2);
	it++;
	it++;
	it++;
	it++;
	it++;
	it++;
	it++;
	it++;
	it++;
}