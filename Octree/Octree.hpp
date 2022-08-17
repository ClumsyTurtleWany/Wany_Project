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
	void create(Box_<T> _box);
	void create(T _width, T _height, T _depth);
	void create(Point3D_<T> _pos, T _width, T _height, T _depth);

	node<T>* createNode(Point3D_<T> _pos, T _width, T _height, T _depth, node<T>* _parent = nullptr);
	void buildTree(node<T>* _parent);
	node<T>* findNode(node<T>* _parent, object3D<T>* _obj);
	node<T>* getNode(object3D<T>* _obj);
	void addObject(object3D<T>* _obj);
	bool Collision(object3D<T>* _src, std::vector<object3D<T>*>* _dst, std::vector<Box_<T>>* _dstSection = nullptr);
	bool getCollisionObject(node<T>* _node, object3D<T>* _src, std::vector<object3D<T>*>* _dst, std::vector<Box_<T>>* _dstSection = nullptr);
	void resetDynamicObject(node<T>* _target);
	void updateDynamicObject();
	void updateDynamicObject(node<T>* _target, std::vector<object3D<T>*>* _list);
	
	bool isHitMinX(object3D<T>* _obj);
	bool isHitMaxX(object3D<T>* _obj);
	bool isHitMinY(object3D<T>* _obj);
	bool isHitMaxY(object3D<T>* _obj);
	bool isHitMinZ(object3D<T>* _obj);
	bool isHitMaxZ(object3D<T>* _obj);
	bool isHitBoundary(object3D<T>* _obj);
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
		root = nullptr;
	}
}

template <typename T>
void Octree<T>::create(Box_<T> _box)
{
	create(_box.pos, _box.width, _box.height, _box.depth);
}

template <typename T>
void Octree<T>::create(T _width, T _height, T _depth)
{
	create(Point3D_<T>(0, 0, 0), _width, _height, _depth);
}

template <typename T>
void Octree<T>::create(Point3D_<T> _pos, T _width, T _height, T _depth)
{
	if (root == nullptr)
	{
		root = createNode(_pos, _width, _height, _depth);
		buildTree(root);
	}
	else
	{
		delete root;
		root = createNode(_pos, _width, _height, _depth);
		buildTree(root);
	}
}

template <typename T>
node<T>* Octree<T>::createNode(Point3D_<T> _pos, T _width, T _height, T _depth, node<T>* _parent)
{
	node<T>* newNode = new node<T>(_pos, _width, _height, _depth, _parent);
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

	T width = static_cast<T>(_parent->box.width / 2.0f);
	T height = static_cast<T>(_parent->box.height / 2.0f);
	T depth = static_cast<T>(_parent->box.height / 2.0f);
	_parent->child[0] = createNode(
		Point3D_<T>(_parent->box.pos.x,	
					_parent->box.pos.y, 
					_parent->box.pos.z),
		width,
		height,
		depth,
		_parent);

	_parent->child[1] = createNode(
		Point3D_<T>(_parent->box.pos.x + width,
					_parent->box.pos.y,
					_parent->box.pos.z),
		width,
		height,
		depth,
		_parent);

	_parent->child[2] = createNode(
		Point3D_<T>(_parent->box.pos.x,
					_parent->box.pos.y + height,
					_parent->box.pos.z),
		width,
		height,
		depth,
		_parent);

	_parent->child[3] = createNode(
		Point3D_<T>(_parent->box.pos.x + width,
					_parent->box.pos.y + height,
					_parent->box.pos.z),
		width,
		height,
		depth,
		_parent);

	_parent->child[4] = createNode(
		Point3D_<T>(_parent->box.pos.x,
			_parent->box.pos.y,
			_parent->box.pos.z + depth),
		width,
		height,
		depth,
		_parent);

	_parent->child[5] = createNode(
		Point3D_<T>(_parent->box.pos.x + width,
			_parent->box.pos.y,
			_parent->box.pos.z + depth),
		width,
		height,
		depth,
		_parent);

	_parent->child[6] = createNode(
		Point3D_<T>(_parent->box.pos.x,
			_parent->box.pos.y + height,
			_parent->box.pos.z + depth),
		width,
		height,
		depth,
		_parent);

	_parent->child[7] = createNode(
		Point3D_<T>(_parent->box.pos.x + width,
			_parent->box.pos.y + height,
			_parent->box.pos.z + depth),
		width,
		height,
		depth,
		_parent);


	for (int i = 0; i < CHILD_NODE_CNT; i++)
	{
		buildTree(_parent->child[i]);
	}
}

template <typename T>
node<T>* Octree<T>::findNode(node<T>* _parent, object3D<T>* _obj)
{
	node<T>* temp = _parent;
	while (temp != nullptr)
	{
		bool isIn = false;
		for (int i = 0; i < CHILD_NODE_CNT; i++)
		{
			if (temp->child[i] != nullptr)
			{
				if (temp->child[i]->box.BoxInBox(_obj->box))
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
node<T>* Octree<T>::getNode(object3D<T>* _obj)
{
	return findNode(root, _obj);
}

template <typename T>
void Octree<T>::addObject(object3D<T>* _obj)
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
bool Octree<T>::Collision(object3D<T>* _src, std::vector<object3D<T>*>* _dst, std::vector<Box_<T>>* _dstSection)
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
bool Octree<T>::getCollisionObject(node<T>* _node, object3D<T>* _src, std::vector<object3D<T>*>* _dst, std::vector<Box_<T>>* _dstSection)
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

				if (_src->getSphere().intersectSphere(it->getSphere()))
				{
					Box_<T> intersection;
					isCollision = _src->box.intersectBox(it->box, &intersection);
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

				if (_src->getSphere().intersectSphere(it->getSphere()))
				{
					Box_<T> intersection;
					isCollision = _src->box.intersectBox(it->box, &intersection);
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
	std::vector<object3D<T>*> objList;
	updateDynamicObject(root, &objList);

	for (auto it : objList)
	{
		addObject(it);
	}
}

template <typename T>
void Octree<T>::updateDynamicObject(node<T>* _target, std::vector<object3D<T>*>* _list)
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
inline bool Octree<T>::isHitMinX(object3D<T>* _obj)
{
	return root->isHitMinX(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitMaxX(object3D<T>* _obj)
{
	return root->isHitMaxX(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitMinY(object3D<T>* _obj)
{
	return root->isHitMinY(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitMaxY(object3D<T>* _obj)
{
	return root->isHitMaxY(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitMinZ(object3D<T>* _obj)
{
	return root->isHitMinZ(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitMaxZ(object3D<T>* _obj)
{
	return root->isHitMaxZ(_obj, true);
}

template<typename T>
inline bool Octree<T>::isHitBoundary(object3D<T>* _obj)
{
	return root->isHitBoundary(_obj, true);
}
