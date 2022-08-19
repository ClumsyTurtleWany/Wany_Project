#pragma once
#include "SpaceDivision.hpp"

// 공간 분할(Space Division) 알고리즘을 위한 Quad Tree
static const int QuadTreeChildNum = 8;

template <typename T>
class QuadTree : public SpaceDivision<Rect_<T>, object2D<T>>
{
public:
	node2D<T>* root = nullptr;

public:
	QuadTree();
	~QuadTree();

public:
	void create(Rect_<T> _rect) override;
	void create(T _width, T _height);
	void create(T _x, T _y, T _width, T _height);

	void addObject(object2D<T>* _obj) override;
	bool Collision(object2D<T>* _src, std::vector<object2D<T>*>* _dst, std::vector<Rect_<T>>* _dstSection = nullptr) override;
	void updateDynamicObject() override;
	
public:
	node2D<T>* createNode(T _x, T _y, T _width, T _height, node2D<T>* _parent = nullptr);
	void buildTree(node2D<T>* _parent);
	node2D<T>* findNode(node2D<T>* _parent, object2D<T>* _obj);
	node2D<T>* getNode(object2D<T>* _obj);
	bool getCollisionObject(node2D<T>* _node, object2D<T>* _src, std::vector<object2D<T>*>* _dst, std::vector<Rect_<T>>* _dstSection = nullptr);
	void resetDynamicObject(node2D<T>* _target);
	void updateDynamicObject(node2D<T>* _target, std::vector<object2D<T>*>* _list);

public:
	bool isHitLeft(object2D<T>* _obj);
	bool isHitRight(object2D<T>* _obj);
	bool isHitTop(object2D<T>* _obj);
	bool isHitBottom(object2D<T>* _obj);
	bool isHitBoundary(object2D<T>* _obj);
};

template <typename T>
QuadTree<T>::QuadTree()
{
}

template <typename T>
QuadTree<T>::~QuadTree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

template <typename T>
void QuadTree<T>::create(Rect_<T> _rect)
{
	create(_rect.LT.x, _rect.LT.y, _rect.width(), _rect.height());
}

template <typename T>
void QuadTree<T>::create(T _x, T _y, T _width, T _height)
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
void QuadTree<T>::create(T _width, T _height)
{
	create(0, 0, _width, _height);
}

template <typename T>
node2D<T>* QuadTree<T>::createNode(T _x, T _y, T _width, T _height, node2D<T>* _parent)
{
	node2D<T>* newNode = new node2D<T>(_x, _y, _width, _height, _parent);
	newNode->child.assign(QuadTreeChildNum, nullptr);
	return newNode;
}

template <typename T>
void QuadTree<T>::buildTree(node2D<T>* _parent)
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

	for (int i = 0; i < QuadTreeChildNum; i++)
	{
		buildTree(_parent->child[i]);
	}
}

template <typename T>
node2D<T>* QuadTree<T>::findNode(node2D<T>* _parent, object2D<T>* _obj)
{
	node2D<T>* temp = _parent;
	while (temp != nullptr)
	{
		bool isIn = false;
		for (int i = 0; i < QuadTreeChildNum; i++)
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
node2D<T>* QuadTree<T>::getNode(object2D<T>* _obj)
{
	return findNode(root, _obj);
}

template <typename T>
void QuadTree<T>::addObject(object2D<T>* _obj)
{
	node2D<T>* target = findNode(root, _obj);
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
bool QuadTree<T>::Collision(object2D<T>* _src, std::vector<object2D<T>*>* _dst, std::vector<Rect_<T>>* _dstSection)
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
bool QuadTree<T>::getCollisionObject(node2D<T>* _node, object2D<T>* _src, std::vector<object2D<T>*>* _dst, std::vector<Rect_<T>>* _dstSection)
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

				if (_src->getCircle().intersectCircle(it->getCircle()))
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

				if (_src->getCircle().intersectCircle(it->getCircle()))
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
			for (int cnt = 0; cnt < QuadTreeChildNum; cnt++)
			{
				isCollision |= getCollisionObject(_node->child[cnt], _src, _dst, _dstSection);
			}
		}

		return isCollision;
	}
}

template <typename T>
void QuadTree<T>::resetDynamicObject(node2D<T>* _target)
{
	if (_target == nullptr)
	{
		return;
	}

	_target->dyObjList.clear();
	for (int cnt = 0; cnt < QuadTreeChildNum; cnt++)
	{
		resetDynamicObject(_target->child[cnt]);
	}
}

template <typename T>
void QuadTree<T>::updateDynamicObject()
{
	std::vector<object2D<T>*> objList;
	updateDynamicObject(root, &objList);

	for (auto it : objList)
	{
		addObject(it);
	}
}

template <typename T>
void QuadTree<T>::updateDynamicObject(node2D<T>* _target, std::vector<object2D<T>*>* _list)
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

	for (int cnt = 0; cnt < QuadTreeChildNum; cnt++)
	{
		updateDynamicObject(_target->child[cnt], _list);
	}
}

template<typename T>
inline bool QuadTree<T>::isHitLeft(object2D<T>* _obj)
{
	return root->isHitLeft(_obj, true);
}

template<typename T>
inline bool QuadTree<T>::isHitRight(object2D<T>* _obj)
{
	return root->isHitRight(_obj, true);
}

template<typename T>
inline bool QuadTree<T>::isHitTop(object2D<T>* _obj)
{
	return root->isHitTop(_obj, true);
}

template<typename T>
inline bool QuadTree<T>::isHitBottom(object2D<T>* _obj)
{
	return root->isHitBottom(_obj, true);
}

template <typename T>
bool QuadTree<T>::isHitBoundary(object2D<T>* _obj)
{
	return root->isHitBoundary(_obj, true);
}
