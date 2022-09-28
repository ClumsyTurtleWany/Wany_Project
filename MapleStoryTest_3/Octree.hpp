#pragma once
#include "SpaceDivision.hpp"

// 공간 분할(Space Division) 알고리즘을 위한 Octree
static const int OctreeChildNum = 8;

template <typename T>
class Octree : public SpaceDivision //: public SpaceDivision<Box_<T>, object3D<T>>
{
private:
	node3D<T>* root = nullptr;

public:
	Octree();
	~Octree();

public:
	void create(void* _shape) override;
	void addObject(objectBase* _obj) override;
	//objectBase* newPlayer() override;
	//objectBase* newNPC() override;
	//objectBase* newObstacle() override;
	bool Collision(objectBase* _src, std::vector<objectBase*>* _dst, std::vector<void*>* _dstSection = nullptr) override;
	bool checkBorder(objectBase* _target) override;
	void updateDynamicObject() override;
	void render() override;

public:
	void create(Box_<T> _box);
	void create(T _width, T _height, T _depth);
	void create(Point3D_<T> _pos, T _width, T _height, T _depth);
	void addObject(object3D<T>* _obj);

	bool Collision(object3D<T>* _src, std::vector<object3D<T>*>* _dst, std::vector<Box_<T>>* _dstSection = nullptr);
	
	bool checkBorder(object3D<T>* _target);

private:
	node3D<T>* createNode(Point3D_<T> _pos, T _width, T _height, T _depth, node3D<T>* _parent = nullptr);
	void buildTree(node3D<T>* _parent);
	node3D<T>* findNode(node3D<T>* _parent, object3D<T>* _obj);
	node3D<T>* getNode(object3D<T>* _obj);
	bool getCollisionObject(node3D<T>* _node, object3D<T>* _src, std::vector<object3D<T>*>* _dst, std::vector<Box_<T>>* _dstSection = nullptr);
	void resetDynamicObject(node3D<T>* _target);
	void updateDynamicObject(node3D<T>* _target, std::vector<object3D<T>*>* _list);
	
	bool isHitMinX(node3D<T>* _border, object3D<T>* _target, bool _move = false);
	bool isHitMaxX(node3D<T>* _border, object3D<T>* _target, bool _move = false);
	bool isHitMinY(node3D<T>* _border, object3D<T>* _target, bool _move = false);
	bool isHitMaxY(node3D<T>* _border, object3D<T>* _target, bool _move = false);
	bool isHitMinZ(node3D<T>* _border, object3D<T>* _target, bool _move = false);
	bool isHitMaxZ(node3D<T>* _border, object3D<T>* _target, bool _move = false);
};

template <typename T>
Octree<T>::Octree()
{
}

template <typename T>
Octree<T>::~Octree()
{
	if (this->root != nullptr)
	{
		delete this->root;
		this->root = nullptr;
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
	if (this->root == nullptr)
	{
		this->root = createNode(_pos, _width, _height, _depth);
		buildTree(this->root);
	}
	else
	{
		delete this->root;
		this->root = createNode(_pos, _width, _height, _depth);
		buildTree(this->root);
	}
}

template <typename T>
node3D<T>* Octree<T>::createNode(Point3D_<T> _pos, T _width, T _height, T _depth, node3D<T>* _parent)
{
	node3D<T>* newNode = new node3D<T>(Box_<T>(_pos, _width, _height, _depth), _parent);
	newNode->child.assign(OctreeChildNum, nullptr);
	return newNode;
}

template <typename T>
void Octree<T>::buildTree(node3D<T>* _parent)
{
	if (_parent == nullptr)
	{
		return;
	}
	if (_parent->depth >= 3)
	{
		return;
	}

	T width = static_cast<T>(_parent->shape.width / 2.0f);
	T height = static_cast<T>(_parent->shape.height / 2.0f);
	T depth = static_cast<T>(_parent->shape.height / 2.0f);
	_parent->child[0] = createNode(
		Point3D_<T>(_parent->shape.pos.x,
					_parent->shape.pos.y,
					_parent->shape.pos.z),
		width,
		height,
		depth,
		_parent);

	_parent->child[1] = createNode(
		Point3D_<T>(_parent->shape.pos.x + width,
					_parent->shape.pos.y,
					_parent->shape.pos.z),
		width,
		height,
		depth,
		_parent);

	_parent->child[2] = createNode(
		Point3D_<T>(_parent->shape.pos.x,
					_parent->shape.pos.y + height,
					_parent->shape.pos.z),
		width,
		height,
		depth,
		_parent);

	_parent->child[3] = createNode(
		Point3D_<T>(_parent->shape.pos.x + width,
					_parent->shape.pos.y + height,
					_parent->shape.pos.z),
		width,
		height,
		depth,
		_parent);

	_parent->child[4] = createNode(
		Point3D_<T>(_parent->shape.pos.x,
			_parent->shape.pos.y,
			_parent->shape.pos.z + depth),
		width,
		height,
		depth,
		_parent);

	_parent->child[5] = createNode(
		Point3D_<T>(_parent->shape.pos.x + width,
			_parent->shape.pos.y,
			_parent->shape.pos.z + depth),
		width,
		height,
		depth,
		_parent);

	_parent->child[6] = createNode(
		Point3D_<T>(_parent->shape.pos.x,
			_parent->shape.pos.y + height,
			_parent->shape.pos.z + depth),
		width,
		height,
		depth,
		_parent);

	_parent->child[7] = createNode(
		Point3D_<T>(_parent->shape.pos.x + width,
			_parent->shape.pos.y + height,
			_parent->shape.pos.z + depth),
		width,
		height,
		depth,
		_parent);


	for (int i = 0; i < OctreeChildNum; i++)
	{
		buildTree(static_cast<node3D<T>*>(_parent->child[i]));
	}
}

template <typename T>
node3D<T>* Octree<T>::findNode(node3D<T>* _parent, object3D<T>* _obj)
{
	node3D<T>* temp = _parent;
	while (temp != nullptr)
	{
		bool isIn = false;
		for (int i = 0; i < OctreeChildNum; i++)
		{
			if (temp->child[i] != nullptr)
			{
				if (temp->child[i]->shape.BoxInBox(_obj->shape))
				{
					isIn = true;
					temp = static_cast<node3D<T>*>(temp->child[i]);
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
node3D<T>* Octree<T>::getNode(object3D<T>* _obj)
{
	return findNode(this->root, _obj);
}

template <typename T>
void Octree<T>::addObject(object3D<T>* _obj)
{
	node3D<T>* target = findNode(this->root, _obj);
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
bool Octree<T>::getCollisionObject(node3D<T>* _node, object3D<T>* _src, std::vector<object3D<T>*>* _dst, std::vector<Box_<T>>* _dstSection)
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
					isCollision = _src->shape.intersectBox(it->shape, &intersection);
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
					isCollision = _src->shape.intersectBox(it->shape, &intersection);
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
			for (int cnt = 0; cnt < OctreeChildNum; cnt++)
			{
				isCollision |= getCollisionObject(static_cast<node3D<T>*>(_node->child[cnt]), _src, _dst, _dstSection);
			}
		}

		return isCollision;
	}
}

template <typename T>
void Octree<T>::resetDynamicObject(node3D<T>* _target)
{
	if (_target == nullptr)
	{
		return;
	}

	_target->dyObjList.clear();
	for (int cnt = 0; cnt < OctreeChildNum; cnt++)
	{
		resetDynamicObject(_target->child[cnt]);
	}
}

template <typename T>
void Octree<T>::updateDynamicObject()
{
	std::vector<object3D<T>*> objList;
	updateDynamicObject(this->root, &objList);

	for (auto it : objList)
	{
		addObject(it);
	}
}

template <typename T>
void Octree<T>::render()
{

}

template <typename T>
void Octree<T>::updateDynamicObject(node3D<T>* _target, std::vector<object3D<T>*>* _list)
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

	for (int cnt = 0; cnt < OctreeChildNum; cnt++)
	{
		updateDynamicObject(static_cast<node3D<T>*>(_target->child[cnt]), _list);
	}
}

template <typename T>
bool Octree<T>::checkBorder(object3D<T>* _target)
{
	bool isHitBorder = false;
	isHitBorder |= isHitMinX(this->root, _target, true);
	isHitBorder |= isHitMaxX(this->root, _target, true);
	isHitBorder |= isHitMinY(this->root, _target, true);
	isHitBorder |= isHitMaxY(this->root, _target, true);
	isHitBorder |= isHitMinZ(this->root, _target, true);
	isHitBorder |= isHitMaxZ(this->root, _target, true);

	return isHitBorder;
}

template <typename T>
bool Octree<T>::isHitMinX(node3D<T>* _border, object3D<T>* _target, bool _move)
{
	bool isHit = false;
	Box_<T> box = _border->shape;
	if (_target->shape.pos.x < box.pos.x)
	{
		if (_move)
		{
			_target->moveTo(box.pos.x,
				_target->shape.pos.y,
				_target->shape.pos.z);

			_target->velocity.x = 0;
			_target->force.x *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
bool Octree<T>::isHitMaxX(node3D<T>* _border, object3D<T>* _target, bool _move)
{
	bool isHit = false;
	Box_<T> box = _border->shape;
	if (_target->shape.maxp().x > box.maxp().x)
	{
		if (_move)
		{
			_target->moveTo(box.maxp().x - _target->shape.width,
				_target->shape.pos.y,
				_target->shape.pos.z);

			_target->velocity.x = 0;
			_target->force.x *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
bool Octree<T>::isHitMinY(node3D<T>* _border, object3D<T>* _target, bool _move)
{
	bool isHit = false;
	Box_<T> box = _border->shape;
	if (_target->shape.pos.y < box.pos.y)
	{
		if (_move)
		{
			_target->moveTo(_target->shape.pos.x,
				box.pos.y,
				_target->shape.pos.z);

			_target->velocity.y = 0;
			_target->force.y *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
bool Octree<T>::isHitMaxY(node3D<T>* _border, object3D<T>* _target, bool _move)
{
	bool isHit = false;
	Box_<T> box = _border->shape;
	if (_target->shape.maxp().y > box.maxp().y)
	{
		if (_move)
		{
			_target->moveTo(_target->shape.pos.x,
				box.maxp().y - _target->shape.height,
				_target->shape.pos.z);

			_target->velocity.y = 0;
			_target->force.y *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
bool Octree<T>::isHitMinZ(node3D<T>* _border, object3D<T>* _target, bool _move)
{
	bool isHit = false;
	Box_<T> box = _border->shape;
	if (_target->shape.pos.z < box.pos.z)
	{
		if (_move)
		{
			_target->moveTo(_target->shape.pos.x,
				_target->shape.pos.y,
				box.pos.z);

			_target->velocity.z = 0;
			_target->force.z *= -1;
		}
		isHit = true;
	}
	return isHit;
}

template <typename T>
bool Octree<T>::isHitMaxZ(node3D<T>* _border, object3D<T>* _target, bool _move)
{
	bool isHit = false;
	Box_<T> box = _border->shape;
	if (_target->shape.maxp().z > box.maxp().z)
	{
		if (_move)
		{
			_target->moveTo(_target->shape.pos.x,
				_target->shape.pos.y,
				box.maxp().z - _target->shape.depth);

			_target->velocity.z = 0;
			_target->force.z *= -1;
		}
		isHit = true;
	}
	return isHit;
}




template <typename T>
void Octree<T>::create(void* _shape)
{
	create(*(Box_<T>*)_shape);
}

template <typename T>
void Octree<T>::addObject(objectBase* _obj)
{
	addObject(static_cast<object3D<T>*>(_obj));
}

//template <typename T>
//objectBase* Octree<T>::newPlayer()
//{
//	return new Player3D<T>;
//}
//
//template <typename T>
//objectBase* Octree<T>::newNPC()
//{
//	return new NPC3D<T>;
//}
//
//template <typename T>
//objectBase* Octree<T>::newObstacle()
//{
//	return new Obstacle3D<T>;
//}

template <typename T>
bool Octree<T>::Collision(objectBase* _src, std::vector<objectBase*>* _dst, std::vector<void*>* _dstSection)
{
	if (this->root == nullptr || _src == nullptr)
	{
		return false;
	}
	else
	{
		bool isExist = false;
		object3D<T>* src = dynamic_cast<object3D<T>*>(_src);
		std::vector<object3D<T>*> dst;
		std::vector<Box_<T>> dstSection;
		isExist |= getCollisionObject(this->root, src, &dst, &dstSection);
		for (auto it : dst)
		{
			_dst->push_back(it);
		}

		return isExist;
	}
}

template <typename T>
bool Octree<T>::checkBorder(objectBase* _target)
{
	return checkBorder(static_cast<object3D<T>*>(_target));
}