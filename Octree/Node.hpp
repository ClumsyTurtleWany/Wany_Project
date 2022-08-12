#pragma once
#include <vector>
#include "Object.hpp"

#define CHILD_NODE_CNT (int)4

template <typename T>
class node
{
public:
	Rect_<T> rect;
	int depth = 0;

	std::vector<object<T>*> stObjList;
	std::vector<object<T>*> dyObjList;
	node<T>* parent = nullptr;
	node<T>* child[CHILD_NODE_CNT] = { nullptr, };

public:
	node(Rect_<T> _rect, node<T>* _parent = nullptr)
	{
		rect = _rect;
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	}

	node(T _x, T _y, T _w, T _h, node<T>* _parent = nullptr)
	{
		rect = Rect_<T>(_x, _y, _w, _h);
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

	bool isHitLeft(object<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		if (_obj->rect.left() < rect.left())
		{
			if (_move)
			{
				_obj->moveTo(rect.left(), _obj->rect.top());
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitRight(object<T>* _obj, bool _move = false)
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
		return isHit;
	}

	bool isHitTop(object<T>* _obj, bool _move = false)
	{
		bool isHit = false;
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

	bool isHitBottom(object<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		
		if (_obj->rect.bottom() > rect.bottom())
		{
			if (_move)
			{
				_obj->moveTo(_obj->rect.left(), rect.bottom() - _obj->rect.height());
			}
			isHit = true;
		}
		return isHit;
	}
	
	bool isHitBoundary(object<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		isHit |= isHitLeft(_obj, _move);
		isHit |= isHitRight(_obj, _move);
		isHit |= isHitTop(_obj, _move);
		isHit |= isHitBottom(_obj, _move);
		
		return isHit;
	}
};