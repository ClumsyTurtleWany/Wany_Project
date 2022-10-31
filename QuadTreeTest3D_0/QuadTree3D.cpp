#include "QuadTree3D.hpp"

QuadTree3D::QuadTree3D()
{
}

QuadTree3D::~QuadTree3D()
{
}

bool QuadTree3D::create(int _column, int _row, std::vector<Vertex>& _vertexList)
{
	if (_vertexList.empty())
	{
		return false;
	}

	//  0  1  2  3  4
	//  5  6  7  8  9
	// 10 11 12 13 14
	// 15 16 17 18 19
	// 20 21 22 23 24
	int LT = 0;
	int RT = LT + _column - 1;
	int LB = (_row - 1) * _column;
	int RB = LB + _column - 1;
	vertexList.assign(_vertexList.begin(), _vertexList.end());
	if (this->root == nullptr)
	{
		this->root = createNode(LT, RT, LB, RB);
		buildTree(this->root);
	}
	else
	{
		delete this->root;
		this->root = createNode(LT, RT, LB, RB);
		buildTree(this->root);
	}

	return true;
}

node3D<float>* QuadTree3D::createNode(int _LT, int _RT, int _LB, int _RB, node3D<float>* _parent)
{
	Vector3f pos = vertexList[_LT].pos;
	float width = vertexList[_RT].pos.x - vertexList[_LT].pos.x;
	float height = 100.0f;
	float depth = vertexList[_LT].pos.z - vertexList[_LB].pos.z;

	node3D<float>* newNode = new node3D<float>(Box_<float>(Point3f(pos.x, pos.y, pos.z), width, height, depth), _parent);
	newNode->child.assign(QuadTreeChildNum, nullptr);
	newNode->LT = _LT;
	newNode->RT = _RT;
	newNode->LB = _LB;
	newNode->RB = _RB;

	return newNode;
}

bool QuadTree3D::buildTree(node3D<float>* _parent)
{
	if (_parent == nullptr)
	{
		return false;
	}

	if (_parent->depth > 2)
	{
		return false;
	}

	//  0  1  2  3  4
	//  5  6  7  8  9
	// 10 11 12 13 14
	// 15 16 17 18 19
	// 20 21 22 23 24
	int LT = _parent->LT;
	int RT = _parent->RT;
	int LB = _parent->LB;
	int RB = _parent->RB;

	if (((RT - LT) <= 0) || ((RB - LB) <= 0))
	{
		return false;
	}

	int topCenter = (RT + LT) / 2;
	int bottomCenter = (RB + LB) / 2;
	int leftCenter = (LT + LB) / 2;
	int rightCenter = (RT + RB) / 2;
	int center = (leftCenter + rightCenter) / 2;

	if ((topCenter <= LT) || (leftCenter <= LT))
	{
		return false;
	}
	// 0 1
	// 2 3
	_parent->child[0] = createNode(LT, topCenter, leftCenter, center, _parent);
	_parent->child[1] = createNode(topCenter, RT, center, rightCenter, _parent);
	_parent->child[2] = createNode(leftCenter, center, LB, bottomCenter, _parent);
	_parent->child[3] = createNode(center, rightCenter, bottomCenter, RB, _parent);

	for (int idx = 0; idx < QuadTreeChildNum; idx++)
	{
		buildTree((node3D<float>*)_parent->child[idx]);
	}

	return true;
}
