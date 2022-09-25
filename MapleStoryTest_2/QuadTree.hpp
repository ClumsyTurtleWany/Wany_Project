#pragma once
#include "SpaceDivision.hpp"

// 공간 분할(Space Division) 알고리즘을 위한 Quad Tree
static const int QuadTreeChildNum = 4;

template <typename T>
class QuadTree : public SpaceDivision //: public SpaceDivision<Rect_<T>, object2D<T>>
{
private:
	node2D<T>* root = nullptr;

public:
	QuadTree();
	~QuadTree();

public:
	void create(void* _shape) override;
	void addObject(objectBase* _obj) override;
	//objectBase* newPlayer() override;
	//objectBase* newNPC() override;
	//objectBase* newObstacle() override;
	//bool Collision(objectBase* _src, std::vector<objectBase*>* _dst, void* _dstSection = nullptr) override;

	bool Collision(objectBase* _src, std::vector<objectBase*>* _dst, std::vector<Rect_<float>>* _dstSection = nullptr) override;
	bool Collision(objectBase* _src, std::vector<objectBase*>* _dst, std::vector<Box_<float>>* _dstSection = nullptr) override;
	bool checkBorder(objectBase* _target) override;
	void updateDynamicObject() override;
	
public:
	void render() override;
	void renderNode(node2D<T>* _target);

public:
	void create(Rect_<T> _rect);
	void create(T _width, T _height);
	void create(T _x, T _y, T _width, T _height);

	void addObject(object2D<T>* _obj);
	bool Collision(object2D<T>* _src, std::vector<object2D<T>*>* _dst, std::vector<Rect_<T>>* _dstSection = nullptr);
	
	bool checkBorder(object2D<T>* _target);
	
private:
	node2D<T>* createNode(T _x, T _y, T _width, T _height, node2D<T>* _parent = nullptr);
	void buildTree(node2D<T>* _parent);
	node2D<T>* findNode(node2D<T>* _parent, object2D<T>* _obj);
	node2D<T>* getNode(object2D<T>* _obj);
	bool getCollisionObject(node2D<T>* _node, object2D<T>* _src, std::vector<object2D<T>*>* _dst, std::vector<Rect_<T>>* _dstSection = nullptr);
	void resetDynamicObject(node2D<T>* _target);
	void updateDynamicObject(node2D<T>* _target, std::vector<object2D<T>*>* _list);
	
	bool isHitLeft(node2D<T>* _border, object2D<T>* _target, bool _move = false);
	bool isHitRight(node2D<T>* _border, object2D<T>* _target, bool _move = false);
	bool isHitTop(node2D<T>* _border, object2D<T>* _target, bool _move = false);
	bool isHitBottom(node2D<T>* _border, object2D<T>* _target, bool _move = false);
};

template <typename T>
QuadTree<T>::QuadTree()
{
}

template <typename T>
QuadTree<T>::~QuadTree()
{
	if (this->root != nullptr)
	{
		delete this->root;
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
	if (this->root == nullptr)
	{
		this->root = createNode(_x, _y, _width, _height);
		buildTree(this->root);
	}
	else
	{
		delete this->root;
		this->root = createNode(_x, _y, _width, _height);
		buildTree(this->root);
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
	node2D<T>* newNode = new node2D<T>(Rect_<T>(_x, _y, _width, _height), _parent);
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
	if (_parent->shape.width() < 1 || _parent->shape.height() < 1)
	{
		return;
	}

	T width = static_cast<int>(_parent->shape.width() / 2.0f);
	T height = static_cast<int>(_parent->shape.height() / 2.0f);
	_parent->child[0] = createNode(_parent->shape.LT.x,
		_parent->shape.LT.y,
		width,
		height,
		_parent);

	_parent->child[1] = createNode(_parent->shape.LT.x + width,
		_parent->shape.LT.y,
		width,
		height,
		_parent);

	_parent->child[2] = createNode(_parent->shape.LT.x,
		_parent->shape.LT.y + height,
		width,
		height,
		_parent);

	_parent->child[3] = createNode(_parent->shape.LT.x + width,
		_parent->shape.LT.y + height,
		width,
		height,
		_parent);

	for (int i = 0; i < QuadTreeChildNum; i++)
	{
		buildTree(static_cast<node2D<T>*>(_parent->child[i]));
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
				object2D<T>* obj = dynamic_cast<object2D<T>*>(_obj);
				if (temp->child[i]->shape.RectInRect(obj->shape))
				{
					isIn = true;
					temp = static_cast<node2D<T>*>(temp->child[i]);
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
	return findNode(this->root, _obj);
}

template <typename T>
void QuadTree<T>::addObject(object2D<T>* _obj)
{
	node2D<T>* target = findNode(this->root, _obj);
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
	if (this->root == nullptr || _src == nullptr)
	{
		return false;
	}
	else
	{
		bool isExist = false;
		isExist |= getCollisionObject(this->root, _src, _dst, _dstSection);
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

		if (_node->shape.intersectRect(_src->hitbox))
		{
			_node->isCollisionCheck = true;

			if (!_node->stObjList.empty())
			{
				for (auto it : _node->stObjList)
				{
					//if (!_src->rect.RectInRect(it->rect))
					if (_src == it)
					{
						continue;
					}

					//if (_src->getCircle().intersectCircle(it->getCircle()))
					{
						Rect_<T> intersection;
						isCollision = _src->hitbox.intersectRect(it->hitbox, &intersection);
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

					//if (_src->getCircle().intersectCircle(it->getCircle()))
					{
						Rect_<T> intersection;
						isCollision = _src->hitbox.intersectRect(it->hitbox, &intersection);
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
		}
		else
		{
			_node->isCollisionCheck = false;
		}

		if (!_node->isLeaf())
		{
			for (int cnt = 0; cnt < QuadTreeChildNum; cnt++)
			{
				isCollision |= getCollisionObject(static_cast<node2D<T>*>(_node->child[cnt]), _src, _dst, _dstSection);
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
	updateDynamicObject(this->root, &objList);

	for (auto it : objList)
	{
		addObject(it);
	}
}

template<typename T>
inline void QuadTree<T>::render()
{
	renderNode(root);
}

template<typename T>
inline void QuadTree<T>::renderNode(node2D<T>* _target)
{
	if (_target != nullptr)
	{
		for (auto it : _target->child)
		{
			renderNode(static_cast<node2D<T>*>(it));
		}
		_target->render();
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

	_target->isCollisionCheck = false;

	for (int cnt = 0; cnt < QuadTreeChildNum; cnt++)
	{
		updateDynamicObject(static_cast<node2D<T>*>(_target->child[cnt]), _list);
	}
}

template <typename T>
bool QuadTree<T>::checkBorder(object2D<T>* _target)
{
	bool isHitBorder = false;
	isHitBorder |= isHitLeft(this->root, _target, true);
	isHitBorder |= isHitRight(this->root, _target, true);
	isHitBorder |= isHitTop(this->root, _target, true);
	isHitBorder |= isHitBottom(this->root, _target, true);

	return isHitBorder;
}

template <typename T>
bool QuadTree<T>::isHitLeft(node2D<T>* _border, object2D<T>* _target, bool _move)
{
	bool isHit = false;
	Rect_<T> rect = _border->shape;
	if (_target->shape.left() < rect.left())
	{
		if (_move)
		{
			_target->moveTo(rect.left(), _target->shape.top());

			//_target->velocity.x = 0;
			_target->velocity.x *= -0.5;
			_target->force.x *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
bool QuadTree<T>::isHitRight(node2D<T>* _border, object2D<T>* _target, bool _move)
{
	bool isHit = false;
	Rect_<T> rect = _border->shape;
	if (_target->shape.right() > rect.right())
	{
		if (_move)
		{
			_target->moveTo(rect.right() - _target->shape.width(), _target->shape.top());

			//_target->velocity.x = 0;
			_target->velocity.x *= -0.5;
			_target->force.x *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
bool QuadTree<T>::isHitTop(node2D<T>* _border, object2D<T>* _target, bool _move)
{
	bool isHit = false;
	Rect_<T> rect = _border->shape;
	if (_target->shape.top() < rect.top())
	{
		if (_move)
		{
			_target->moveTo(_target->shape.left(), rect.top());

			//_target->velocity.y = 0;
			_target->velocity.y *= -0.5;
			_target->force.y *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
bool QuadTree<T>::isHitBottom(node2D<T>* _border, object2D<T>* _target, bool _move)
{
	bool isHit = false;
	Rect_<T> rect = _border->shape;
	if (_target->shape.bottom() > rect.bottom())
	{
		if (_move)
		{
			_target->moveTo(_target->shape.left(), rect.bottom() - _target->shape.height());

			//_target->velocity.y = 0;
			_target->velocity.y *= -0.5;
			_target->force.y *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
void QuadTree<T>::create(void* _shape)
{
	create(*(Rect_<T>*)_shape);
}

template <typename T>
void QuadTree<T>::addObject(objectBase* _obj)
{
	addObject(static_cast<object2D<T>*>(_obj));
}

//template <typename T>
//objectBase* QuadTree<T>::newPlayer()
//{
//	return new Player2D<T>;
//}
//
//template <typename T>
//objectBase* QuadTree<T>::newNPC()
//{
//	return new NPC2D<T>;
//}
//
//template <typename T>
//objectBase* QuadTree<T>::newObstacle()
//{
//	return new Obstacle2D<T>;
//}

template <typename T>
bool QuadTree<T>::Collision(objectBase* _src, std::vector<objectBase*>* _dst, std::vector<Rect_<float>>* _dstSection)
{
	if (this->root == nullptr || _src == nullptr)
	{
		return false;
	}
	else
	{
		bool isExist = false;
		object2D<T>* src = dynamic_cast<object2D<T>*>(_src);
		std::vector<object2D<T>*> dst;
		std::vector<Rect_<T>> dstSection;
		isExist |= getCollisionObject(this->root, src, &dst, &dstSection);
		for (auto it : dst)
		{
			_dst->push_back(it);
		}

		for (auto it : dstSection)
		{
			_dstSection->push_back(it);
		}
		return isExist;
	}
}

template <typename T>
bool QuadTree<T>::Collision(objectBase* _src, std::vector<objectBase*>* _dst, std::vector<Box_<float>>* _dstSection)
{
	return true;
}


template <typename T>
bool QuadTree<T>::checkBorder(objectBase* _target)
{
	return checkBorder(static_cast<object2D<T>*>(_target));
}