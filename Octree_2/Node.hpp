#pragma once
#include <vector>
#include "Object.hpp"

template <class Shape, class ObjectDimension>
class node
{
public:
	node<Shape, ObjectDimension>* parent = nullptr;
	std::vector<node<Shape, ObjectDimension>*> child;

	int depth = 0;

	Shape shape;

	std::vector<ObjectDimension*> stObjList;
	std::vector<ObjectDimension*> dyObjList;
	
public:
	node(Shape _shape, node<Shape, ObjectDimension>* _parent = nullptr)
	{
		shape = _shape;
		if (_parent != nullptr)
		{
			parent = _parent;
			depth = _parent->depth + 1;
		}
	}

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
};


template <typename T>
class node2D : public node<Rect_<T>, object2D<T>>
{
public:
	node2D(Rect_<T> _rect, node2D<T>* _parent = nullptr)
	{
		this->shape = _rect;
		if (_parent != nullptr)
		{
			this->parent = _parent;
			this->depth = _parent->depth + 1;
		}
	}

	node2D(Rect_<T> _rect, node<Rect_<T>, object2D<T>>* _parent = nullptr)
	{
		this->shape = _rect;
		if (_parent != nullptr)
		{
			this->parent = _parent;
			this->depth = _parent->depth + 1;
		}
	}

	node2D(T _x, T _y, T _w, T _h, node2D<T>* _parent = nullptr)
	{
		this->shape = Rect_<T>(_x, _y, _w, _h);
		if (_parent != nullptr)
		{
			this->parent = _parent;
			this->depth = _parent->depth + 1;
		}
	};
};

template <typename T>
class node3D : public node<Box_<T>, object3D<T>>
{
public:
	node3D(Box_<T> _box, node3D<T>* _parent = nullptr)
	{
		this->shape = _box;
		if (_parent != nullptr)
		{
			this->parent = _parent;
			this->depth = _parent->depth + 1;
		}
	}

	node3D(void* _box, void* _parent = nullptr)
	{
		this->shape = (Box_<T>)_box;
		if (_parent != nullptr)
		{
			this->parent = (node3D<T>*)_parent;
			this->depth = _parent->depth + 1;
		}
	}

	node3D(Box_<T> _box, void* _parent = nullptr)
	{
		this->shape = _box;
		if (_parent != nullptr)
		{
			this->parent = (node3D<T>*)_parent;
			this->depth = _parent->depth + 1;
		}
	}

	node3D(Box_<T> _box, node<Box_<T>, object3D<T>>* _parent = nullptr)
	{
		this->shape = _box;
		if (_parent != nullptr)
		{
			this->parent = _parent;
			this->depth = _parent->depth + 1;
		}
	}

	node3D(Point3D_<T> _pos, T _width, T _height, T _depth, node3D<T>* _parent = nullptr)
	{
		this->shape = Box_<T>(_pos, _width, _height, _depth);
		if (_parent != nullptr)
		{
			this->parent = _parent;
			this->depth = _parent->depth + 1;
		}
	}
};