#pragma once
#include "Node.hpp"

// 공간 분할(Space Division) 알고리즘을 위한 Quad Tree

class QuadTree
{
public:
	node* root = nullptr;

public:
	QuadTree();
	~QuadTree();
	void create(Rect _rect);
	void create(int _width, int _height);
	void create(int _x, int _y, int _width, int _height);
	
	node* createNode(int _x, int _y, int _width, int _height, node* _parent = nullptr);
	void buildTree(node* _parent);
	node* findNode(node* _parent, object* _obj);
	node* getNode(object* _obj);
	void addObject(object* _obj);
	bool Collision(object* _src, ObjectList* _dst, std::vector<Rect>* _dstSection = nullptr);
	bool getCollisionObject(node* _node, object* _src, ObjectList* _dst, std::vector<Rect>* _dstSection = nullptr);
	void resetDynamicObject(node* _target);
	void updateDynamicObject();
	void updateDynamicObject(node* _target, ObjectList* _list);
	bool isBoundaryHit(object* _obj);
};