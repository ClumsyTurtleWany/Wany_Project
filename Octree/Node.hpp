#pragma once
#include <vector>
#include "Object.hpp"

#define CHILD_NODE_CNT (int)8

class node
{
public:
	Rect rect;
	int depth = 0;

	std::vector<object*> objList;
	node* parent = nullptr;
	node* child[CHILD_NODE_CNT] = { nullptr, };

public:
	node(Rect _rect, node* _parent = nullptr)
	{
		rect = _rect;
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	}

	node(int _x, int _y, int _w, int _h, node* _parent = nullptr)
	{
		rect = Rect(_x, _y, _w, _h);
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	};

	~node()
	{
		if (!objList.empty())
		{
			for (auto& it : objList)
			{
				delete it;
			}
			objList.clear();
		}

		for (int i = 0; i < CHILD_NODE_CNT; i++)
		{
			if (child[i] != nullptr)
			{
				delete child[i];
				child[i] = nullptr;
			}
		}
	}

	bool isLeaf()
	{
		bool isNullptr = true;
		for (int cnt = 0; cnt < CHILD_NODE_CNT; cnt++)
		{
			if (child[cnt] == nullptr)
			{
				isNullptr &= true;
			}
		}
		
		return isNullptr;
	}
};