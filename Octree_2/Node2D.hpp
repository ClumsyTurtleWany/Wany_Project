#pragma once
#include <vector>
#include "Object2D.hpp"

template <typename T>
class node2D
{
public:
	Rect_<T> rect;
	int depth = 0;

	std::vector<object2D<T>*> stObjList;
	std::vector<object2D<T>*> dyObjList;
	node2D<T>* parent = nullptr;
	std::vector<node2D<T>*> child;

public:
	node2D(Rect_<T> _rect, node2D<T>* _parent = nullptr)
	{
		rect = _rect;
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	}

	node2D(T _x, T _y, T _w, T _h, node2D<T>* _parent = nullptr)
	{
		rect = Rect_<T>(_x, _y, _w, _h);
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	};

	~node2D()
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

		if (!child.empty())
		{
			for (auto it : child)
			{
				delete it;
			}
			child.clear();
		}
	}

	bool isLeaf()
	{
		bool bIsLeaf = true;
		for (auto it : child)
		{
			bIsLeaf &= (it == nullptr);
		}

		return bIsLeaf;
	}

	bool isHitLeft(object2D<T>* _obj, bool _move = false)
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

	bool isHitRight(object2D<T>* _obj, bool _move = false)
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

	bool isHitTop(object2D<T>* _obj, bool _move = false)
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

	bool isHitBottom(object2D<T>* _obj, bool _move = false)
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

	bool isHitBoundary(object2D<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		isHit |= isHitLeft(_obj, _move);
		isHit |= isHitRight(_obj, _move);
		isHit |= isHitTop(_obj, _move);
		isHit |= isHitBottom(_obj, _move);

		return isHit;
	}
};