#include "QuadTree.hpp"

QuadTree::QuadTree()
{
}

QuadTree::~QuadTree()
{
}

void QuadTree::create(Rect _rect)
{
	create(_rect.x, _rect.y, _rect.width, _rect.height);
}

void QuadTree::create(int _x, int _y, int _width, int _height)
{
	if (root == nullptr)
	{
		root = createNode(_x, _y, _width, _height);
		buildTree(root);
	}
	else
	{
		delete root;
		root = createNode(_x, _y, _width, _height);
		buildTree(root);
	}
}

void QuadTree::create(int _width, int _height)
{
	create(0, 0, _width, _height);
}

node* QuadTree::createNode(int _x, int _y, int _width, int _height, node* _parent)
{
	node* newNode = new node(_x, _y, _width, _height, _parent);
	return newNode;
}

void QuadTree::buildTree(node* _parent)
{
	if (_parent == nullptr)
	{
		return;
	}
	if (_parent->depth >=  3)
	{
		return;
	}
	if (_parent->rect.width < 1 || _parent->rect.height < 1)
	{
		return;
	}

	int width = static_cast<int>(_parent->rect.width / 2.0f);
	int height = static_cast<int>(_parent->rect.height / 2.0f);
	_parent->child[0] = createNode(	_parent->rect.x, 
									_parent->rect.y, 
									width,
									height,
									_parent);

	_parent->child[1] = createNode(	_parent->rect.x + width,
									_parent->rect.y,
									width,
									height,
									_parent);

	_parent->child[2] = createNode(	_parent->rect.x,
									_parent->rect.y + height,
									width,
									height,
									_parent);

	_parent->child[3] = createNode(	_parent->rect.x + width,
									_parent->rect.y + height,
									width,
									height,
									_parent);
	
	for (int i = 0; i < CHILD_NODE_CNT; i++)
	{
		buildTree(_parent->child[i]);
	}
}

node* QuadTree::findNode(node* _parent, object* _obj)
{
	node* temp = _parent;
	while (temp != nullptr)
	{
		bool isIn = false;
		for (int i = 0; i < CHILD_NODE_CNT; i++)
		{
			if (temp->child[i] != nullptr)
			{
				if (temp->child[i]->rect.rectInRect(_obj->rect))
				{
					isIn = true;
					temp = temp->child[i];
					break;
				}
			}
		}
		if (!isIn)
		{
			break;
		}
	}
	
	return temp;
}

void QuadTree::addObject(object* _obj)
{
	node* target = findNode(root, _obj);
	if (target != nullptr)
	{
		if (_obj->type == OBJECT_TYPE::STATIC_OBJECT)
		{
			target->stObjList.push_back(_obj);
		}
		else
		{
			target->dyObjList.push_back(_obj);
		}
	}
}