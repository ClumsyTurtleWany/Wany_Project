#include "QuadTree.hpp"

QuadTree::QuadTree()
{
}

QuadTree::~QuadTree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

void QuadTree::create(Rect _rect)
{
	create(_rect.LT.x, _rect.LT.y, _rect.width(), _rect.height());
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
	if (_parent->rect.width() < 1 || _parent->rect.height() < 1)
	{
		return;
	}

	int width = static_cast<int>(_parent->rect.width() / 2.0f);
	int height = static_cast<int>(_parent->rect.height() / 2.0f);
	_parent->child[0] = createNode(	_parent->rect.LT.x, 
									_parent->rect.LT.y, 
									width,
									height,
									_parent);

	_parent->child[1] = createNode(	_parent->rect.LT.x + width,
									_parent->rect.LT.y,
									width,
									height,
									_parent);

	_parent->child[2] = createNode(	_parent->rect.LT.x,
									_parent->rect.LT.y + height,
									width,
									height,
									_parent);

	_parent->child[3] = createNode(	_parent->rect.LT.x + width,
									_parent->rect.LT.y + height,
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
				if (temp->child[i]->rect.RectInRect(_obj->rect))
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

node* QuadTree::getNode(object* _obj)
{
	return findNode(root, _obj);
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

bool QuadTree::Collision(object* _src, ObjectList* _dst, std::vector<Rect>* _dstSection)
{
	if (root == nullptr || _src == nullptr)
	{
		return false;
	}
	else
	{
		bool isExist = false;
		isExist |= getCollisionObject(root, _src, _dst, _dstSection);
		return isExist;
	}
}

bool QuadTree::getCollisionObject(node* _node, object* _src, ObjectList* _dst, std::vector<Rect>* _dstSection)
{
	if (_node == nullptr)
	{
		return false;
	}
	else
	{
		bool isCollision = false;
		if (!_node->stObjList.empty())
		{
			for (auto it : _node->stObjList)
			{
				//if (!_src->rect.RectInRect(it->rect))
				if (_src == it)
				{
					continue;
				}

				if (_src->circle.intersectCircle(it->circle))
				{
					Rect intersection;
					isCollision = _src->rect.intersectRect(it->rect, &intersection);
					if (isCollision)
					{
						_dst->push_back(it);
						if (_dstSection != nullptr)
						{
							_dstSection->push_back(intersection);
						}
					}
				}
			}
		}

		if (!_node->dyObjList.empty())
		{
			for (auto it : _node->dyObjList)
			{
				//if (!_src->rect.RectInRect(it->rect))
				if (_src == it)
				{
					continue;
				}

				if (_src->circle.intersectCircle(it->circle))
				{
					Rect intersection;
					isCollision = _src->rect.intersectRect(it->rect, &intersection);
					if (isCollision)
					{
						_dst->push_back(it);
						if (_dstSection != nullptr)
						{
							_dstSection->push_back(intersection);
						}
					}
				}
			}
		}

		if (!_node->isLeaf())
		{
			for (int cnt = 0; cnt < CHILD_NODE_CNT; cnt++)
			{
				isCollision |= getCollisionObject(_node->child[cnt], _src, _dst, _dstSection);
			}
		}

		return isCollision;
	}
}

void QuadTree::resetDynamicObject(node* _target)
{
	if (_target == nullptr)
	{
		return;
	}

	_target->dyObjList.clear();
	for (int cnt = 0; cnt < CHILD_NODE_CNT; cnt++)
	{
		resetDynamicObject(_target->child[cnt]);
	}
}

void QuadTree::updateDynamicObject()
{
	std::vector<object*> objList;
	updateDynamicObject(root, &objList);

	for (auto it : objList)
	{
		addObject(it);
	}
}

void QuadTree::updateDynamicObject(node* _target, ObjectList* _list)
{
	if (_target == nullptr)
	{
		return;
	}

	if (!_target->dyObjList.empty())
	{
		for (auto it : _target->dyObjList)
		{
			_list->push_back(it);
		}
	}
	_target->dyObjList.clear();

	for (int cnt = 0; cnt < CHILD_NODE_CNT; cnt++)
	{
		updateDynamicObject(_target->child[cnt], _list);
	}
}

bool QuadTree::isBoundaryHit(object* _obj)
{
	bool isHit = false;
	if (_obj->rect.right() > root->rect.right())
	{
		_obj->moveTo(root->rect.right() - _obj->rect.width(), _obj->rect.top());
		isHit = true;
	}
	if (_obj->rect.left() < root->rect.left())
	{
		_obj->moveTo(root->rect.left(), _obj->rect.top());
		isHit = true;
	}
	if (_obj->rect.bottom() > root->rect.bottom())
	{
		_obj->moveTo(_obj->rect.left(), root->rect.bottom() - _obj->rect.height());
		isHit = true;
	}
	if (_obj->rect.top() < root->rect.top())
	{
		_obj->moveTo(_obj->rect.left(), root->rect.top());
		isHit = true;
	}
	return isHit;
}
