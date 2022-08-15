#pragma once
#include <vector>
#include "Object.hpp"

#define CHILD_NODE_CNT (int)8

template <typename T>
class node
{
public:
	Cube_<T> cube;

	int depth = 0;

	std::vector<object<T>*> stObjList;
	std::vector<object<T>*> dyObjList;
	node<T>* parent = nullptr;
	node<T>* child[CHILD_NODE_CNT] = { nullptr, };

public:
	node(Cube_<T> _cube, node<T>* _parent = nullptr)
	{
		cube = _cube;
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	}

	node(Point3D_<T> _pos, T _size, float _theta, float _pi, node<T>* _parent = nullptr)
	{
		cube = Cube_<T>(_pos, _size, _theta, _pi);
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	}

	node(T _x, T _y, T _z, T _size, float _theta, float _pi, node<T>* _parent = nullptr)
	{
		cube = Cube_<T>(_x, _y, _z, _size, _theta, _pi);
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
		if (_obj->cube.left() < cube.left())
		{
			if (_move)
			{
				_obj->moveTo(cube.left(), _obj->cube.top());
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitRight(object<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		if (_obj->cube.right() > cube.right())
		{
			if (_move)
			{
				_obj->moveTo(cube.right() - _obj->cube.width(), _obj->cube.top());
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitTop(object<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		if (_obj->cube.top() < cube.top())
		{
			if (_move)
			{
				_obj->moveTo(_obj->cube.left(), cube.top());
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitBottom(object<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		
		if (_obj->cube.bottom() > cube.bottom())
		{
			if (_move)
			{
				_obj->moveTo(_obj->cube.left(), cube.bottom() - _obj->cube.height());
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