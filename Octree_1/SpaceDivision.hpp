#pragma once
#include "Node.hpp"
#include "Node2D.hpp"

template <typename T>
class SpaceDivision
{
public:
	SpaceDivision() {};
	virtual ~SpaceDivision() {};
public:
	//// Octree
	//virtual void create(Box_<T> _box) = 0;
	//virtual void create(T _width, T _height, T _depth) = 0;
	//virtual void create(Point3D_<T> _pos, T _width, T _height, T _depth) = 0;

	//virtual void addObject(object3D<T>* _obj) = 0;
	//virtual bool Collision(object3D<T>* _src, std::vector<object3D<T>*>* _dst, std::vector<Box_<T>>* _dstSection = nullptr) = 0;

	//// QuadTree
	//virtual void create(Rect_<T> _rect) = 0;
	//virtual void create(T _width, T _height) = 0;
	//virtual void create(T _x, T _y, T _width, T _height) = 0;

	//virtual void addObject(object2D<T>* _obj) = 0;
	//virtual bool Collision(object2D<T>* _src, std::vector<object2D<T>*>* _dst, std::vector<Rect_<T>>* _dstSection = nullptr) = 0;

	//// Common
	//virtual void updateDynamicObject() = 0;
};
