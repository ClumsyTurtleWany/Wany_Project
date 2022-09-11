#pragma once
#include <vector>
#include "Object.hpp"
#include "DXShaderBorder.hpp"

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
	node() {};
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
	object2D<T> obj;

public:
	node2D(Rect_<T> _rect, node2D<T>* _parent = nullptr)
	{
		this->shape = _rect;
		if (_parent != nullptr)
		{
			this->parent = _parent;
			this->depth = _parent->depth + 1;
		}

		obj.createShader(ShaderType::Border);
		obj.shape = this->shape;
		obj.pShader->setColor(Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
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

	void setColor(const Vector4f& _color)
	{
		obj.pShader->setColor(_color);
	}

	void render()
	{
		RECT clientRect = g_pWindow->getClientRect();
		float mapWidth = clientRect.right - clientRect.left; // clientRectWidth;
		float mapHeight = clientRect.bottom - clientRect.top; // clientRectHeight;
		float mapWidth_Half = mapWidth * 0.5;
		float mapHeight_Half = mapHeight * 0.5;

		Rect_<float> rectNDC;
		rectNDC.LT.x = (this->shape.LT.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.LT.y = -(this->shape.LT.y - mapHeight_Half) / mapHeight_Half;
		rectNDC.RB.x = (this->shape.RB.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.RB.y = -(this->shape.RB.y - mapHeight_Half) / mapHeight_Half;

		std::vector<Vertex>* list = obj.pShader->getVertexList();
		list->at(0).pos = {rectNDC.LT.x, rectNDC.LT.y, 0.0f};
		list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

		list->at(0).texture = { 0.0f, 0.0f }; // p1-LT
		list->at(1).texture = { 1.0f, 0.0f }; // p2-RT
		list->at(2).texture = { 0.0f, 1.0f }; // p3-LB
		list->at(3).texture = { 1.0f, 1.0f }; // p4-RB

		obj.pShader->render();
	}
};

template <typename T>
class node3D : public node<Box_<T>, object3D<T>>
{
public:
	object3D<T> obj;

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

	node3D(Box_<T> _box, node<Box_<T>, object3D<T>>* _parent = nullptr)
	{
		this->shape = _box;
		if (_parent != nullptr)
		{
			this->parent = _parent;
			this->depth = _parent->depth + 1;
		}
	}
};