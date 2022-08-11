#pragma once
#include <vector>
#include "Object.hpp"

#define CHILD_NODE_CNT (int)4

using ObjectList = std::vector<object*>;
class node
{
public:
	Rect rect;
	int depth = 0;

	ObjectList stObjList;
	ObjectList dyObjList;
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
		if (!stObjList.empty())
		{
			for (auto it : stObjList)
			{
				delete it;
			}
			stObjList.clear();
		}

		if (!dyObjList.empty())
		{
			for (auto it : dyObjList)
			{
				delete it;
			}
			dyObjList.clear();
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
		if (child[0] == nullptr && 
			child[1] == nullptr &&
			child[2] == nullptr &&
			child[3] == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isHitBoundary(object* _obj, bool _move = false)
	{
		bool isHit = false;
		if (_obj->rect.right() > rect.right())
		{
			if (_move)
			{
				_obj->moveTo(rect.right() - _obj->rect.width(), _obj->rect.top());
			}
			isHit = true;
		}
		if (_obj->rect.left() < rect.left())
		{
			if (_move)
			{
				_obj->moveTo(rect.left(), _obj->rect.top());
			}
			isHit = true;
		}
		if (_obj->rect.bottom() > rect.bottom())
		{
			if (_move)
			{
				_obj->moveTo(_obj->rect.left(), rect.bottom() - _obj->rect.height());
			}
			isHit = true;
		}
		if (_obj->rect.top() < rect.top())
		{
			if (_move)
			{
				_obj->moveTo(_obj->rect.left(), rect.top());
			}
			isHit = true;
		}
		return isHit;
	}
};