#include <iostream>
#include "main.h"
#include "LinkedList.hpp"
#include <list>

void main()
{
	LL::List<int> LL_List;
	for (int i = 0; i < 10; i++)
	{
		int data = (i + 1) * 10;
		LL_List.push_back(data);
	}

	LL::List<int>::iterator _iter = LL_List.begin();
	_iter++;
	++_iter;

	int testData = 200;
	LL_List.insert(_iter, testData);

	LL::List<int> LL_List2;
	LL_List2.assign(LL_List.begin(), LL_List.end());

	
	std::list<int> std_List;
	for (int i = 0; i < 10; i++)
	{
		int data = (i + 1) * 10;
		std_List.push_back(data);
	}

	std::list<int>::iterator _iter_std = std_List.begin();
	_iter_std++;
	++_iter_std;

	std_List.insert(_iter_std, 200);

	std_List.sort();

	std::list<int> std_List2;
	std_List2.assign(5, 1);
	std_List2.assign(std_List.begin(), std_List.end());

}
