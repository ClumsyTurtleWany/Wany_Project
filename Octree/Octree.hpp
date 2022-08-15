#pragma once
#include "Node.hpp"

// 공간 분할(Space Division) 알고리즘을 위한 Octree

template <typename T>
class Octree
{
public:
	node<T>* root = nullptr;

public:
	Octree();
	~Octree();
	void create(Rect_<T> _rect);
	void create(T _width, T _height);
	void create(T _x, T _y, T _width, T _height);

	node<T>* createNode(T _x, T _y, T _width, T _height, node<T>* _parent = nullptr);
	void buildTree(node<T>* _parent);
	node<T>* findNode(node<T>* _parent, object<T>* _obj);
	node<T>* getNode(object<T>* _obj);
	void addObject(object<T>* _obj);
	bool Collision(object<T>* _src, std::vector<object<T>*>* _dst, std::vector<Rect_<T>>* _dstSection = nullptr);
	bool getCollisionObject(node<T>* _node, object<T>* _src, std::vector<object<T>*>* _dst, std::vector<Rect_<T>>* _dstSection = nullptr);
	void resetDynamicObject(node<T>* _target);
	void updateDynamicObject();
	void updateDynamicObject(node<T>* _target, std::vector<object<T>*>* _list);

	bool isHitLeft(object<T>* _obj);
	bool isHitRight(object<T>* _obj);
	bool isHitTop(object<T>* _obj);
	bool isHitBottom(object<T>* _obj);
	bool isHitBoundary(object<T>* _obj);
};

template <typename T>
Octree<T>::Octree()
{
}

template <typename T>
Octree<T>::~Octree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

template <typename T>
void Octree<T>::create(Rect_<T> _rect)
{
	create(_rect.LT.x, _rect.LT.y, _rect.width(), _rect.height());
}

template <typename T>
void Octree<T>::create(T _x, T _y, T _width, T _height)
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

template <typename T>
void Octree<T>::create(T _width, T _height)
{
	create(0, 0, _width, _height);
}

template <typename T>
node<T>* Octree<T>::createNode(T _x, T _y, T _width, T _height, node<T>* _parent)
{
	node<T>* newNode = new node<T>(_x, _y, _width, _height, _parent);
	return newNode;
}

template <typename T>
void Octree<T>::buildTree(node<T>* _parent)
{
	if (_parent == nullptr)
	{
		return;
	}
	if (_parent->depth >= 3)
	{
		return;
	}
	if (_parent->rect.width() < 1 || _parent->rect.height() < 1)
	{
		return;
	}

	T width = static_cast<int>(_parent->rect.width() / 2.0f);
	T height = static_cast<int>(_parent->rect.height() / 2.0f);
	_parent->child[0] = createNode(_parent->rect.LT.x,
		_parent->rect.LT.y,
		width,
		height,
		_parent);

	_parent->child[1] = createNode(_parent->rect.LT.x + width,
		_parent->rect.LT.y,
		width,
		height,
		_parent);

	_parent->child[2] = createNode(_parent->rect.LT.x,
		_parent->rect.LT.y + height,
		width,
		height,
		_parent);

	_parent->child[3] = createNode(_parent->rect.LT.x + width,
		_parent->rect.LT.y + height,
		width,
		height,
		_parent);

	for (int i = 0; i < CHILD_NODE_CNT; i++)
	{
		buildTree(_parent->child[i]);
	}
}

template <typename T>
node<T>* Octree<T>::findNode(node<T>* _parent, object<T>* _obj)
{
	node<T>* temp = _parent;
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

template <typename T>
node<T>* Octree<T>::getNode(object<T>* _obj)
{
	return findNode(root, _obj);
}

template <typename T>
void Octree<T>::addObject(object<T>* _obj)
{
	node<T>* target = findNode(root, _obj);
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

template <typename T>
bool Octree<T>::Collision(object<T>* _src, std::vector<object<T>*>* _dst, std::vector<Rect_<T>>* _dstSection)
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

template <typename T>
bool Octree<T>::getCollisionObject(node<T>* _node, object<T>* _src, std::vector<object<T>*>* _dst, std::vector<Rect_<T>>* _dstSection)
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
					Rect_<T> intersection;
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
					Rect_<T> intersection;
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

template <typename T>
void Octree<T>::resetDynamicObject(node<T>* _target)
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

template <typename T>
void Octree<T>::updateDynamicObject()
{
	std::vector<object<T>*> objList;
	updateDynamicObject(root, &objList);

	for (auto it : objList)
	{
		addObject(it);
	}
}

template <typename T>
void Octree<T>::updateDynamicObject(node<T>* _target, std::vector<object<T>*>* _list)
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

template<typename T>
inline bool Octree<T>::isHitLeft(object<T>* _obj)
{
	return root->isHitLeft(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitRight(object<T>* _obj)
{
	return root->isHitRight(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitTop(object<T>* _obj)
{
	return root->isHitTop(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitBottom(object<T>* _obj)
{
	return root->isHitBottom(_obj, true);
}

template <typename T>
bool Octree<T>::isHitBoundary(object<T>* _obj)
{
	return root->isHitBoundary(_obj, true);
}
