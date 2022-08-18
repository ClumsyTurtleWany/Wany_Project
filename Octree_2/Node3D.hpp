#pragma once
#include <vector>
#include "Object3D.hpp"

template <typename T>
class node3D
{
public:
	Box_<T> box;
	int depth = 0;

	std::vector<object3D<T>*> stObjList;
	std::vector<object3D<T>*> dyObjList;
	node3D<T>* parent = nullptr;
	std::vector<node3D<T>*> child;

public:
	node3D(Box_<T> _box, node3D<T>* _parent = nullptr)
	{
		box = _box;
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	}

	node3D(Point3D_<T> _pos, T _width, T _height, T _depth , node3D<T>* _parent = nullptr)
	{
		box = Box_<T>(_pos, _width, _height, _depth);
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	}

	~node3D()
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

	bool isHitMinX(object3D<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		if (_obj->box.pos.x < box.pos.x)
		{
			if (_move)
			{
				_obj->moveTo(box.pos.x, 
					_obj->box.pos.y, 
					_obj->box.pos.z);
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitMaxX(object3D<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		if (_obj->box.maxp().x > box.maxp().x)
		{
			if (_move)
			{
				_obj->moveTo(box.maxp().x - _obj->box.width, 
					_obj->box.pos.y, 
					_obj->box.pos.z);
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitMinY(object3D<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		if (_obj->box.pos.y < box.pos.y)
		{
			if (_move)
			{
				_obj->moveTo(_obj->box.pos.x, 
					box.pos.y, 
					_obj->box.pos.z);
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitMaxY(object3D<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		
		if (_obj->box.maxp().y > box.maxp().y)
		{
			if (_move)
			{
				_obj->moveTo(_obj->box.pos.x, 
					box.maxp().y - _obj->box.height,
					_obj->box.pos.z);
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitMinZ(object3D<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		if (_obj->box.pos.z < box.pos.z)
		{
			if (_move)
			{
				_obj->moveTo(_obj->box.pos.x,
					_obj->box.pos.y,
					box.pos.z);
			}
			isHit = true;
		}
		return isHit;
	}

	bool isHitMaxZ(object3D<T>* _obj, bool _move = false)
	{
		bool isHit = false;

		if (_obj->box.maxp().z > box.maxp().z)
		{
			if (_move)
			{
				_obj->moveTo(_obj->box.pos.x,
					_obj->box.pos.y,
					box.maxp().z - _obj->box.depth);
			}
			isHit = true;
		}
		return isHit;
	}
	
	bool isHitBoundary(object3D<T>* _obj, bool _move = false)
	{
		bool isHit = false;
		isHit |= isHitMinX(_obj, _move);
		isHit |= isHitMaxX(_obj, _move);
		isHit |= isHitMinY(_obj, _move);
		isHit |= isHitMaxY(_obj, _move);
		isHit |= isHitMinZ(_obj, _move);
		isHit |= isHitMaxZ(_obj, _move);
		
		return isHit;
	}
};