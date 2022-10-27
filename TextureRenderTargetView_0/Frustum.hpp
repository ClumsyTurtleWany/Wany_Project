#pragma once
#include "Vector.hpp"
#include "NewObject.hpp"

struct Plane
{
	// 평면의 방정식
	// ax + by + cz + d = 0
	// normal = v0 cross v1 = (a, b, c)
	// d = -(ax + by + cz) = -(normal(a, b, c) dot p0(x, y, z))
	float a, b, c, d;

	bool create(Vector3f _p0, Vector3f _p1, Vector3f _p2)
	{
		Vector3f v0 = _p1 - _p0;
		Vector3f v1 = _p2 - _p0;
		Vector3f normal = v0.cross(v1);
		normal = normal.normalized();
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -(normal.dot(_p0));

		return true;
	}

	bool create(Vector3f _normal, Vector3f _p0)
	{
		Vector3f normal = _normal.normalized();
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -(normal.dot(_p0));

		return true;
	}
};

class Frustum : public object3D<float>
{
public:
	Vector3f FrustumVertexList[8];
	Plane	FrustumPlane[6];

public:
	Matrix4x4 matView;
	Matrix4x4 matProj;

public:
	bool createFrustum(Matrix4x4* _view, Matrix4x4* _proj);

public:
	bool classifyPoint(Vector3f _pos);

public:
	virtual bool initialize() override;
	virtual bool render() override;
};