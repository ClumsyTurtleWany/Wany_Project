#pragma once
#include "Vector.hpp"

#include <d3d11_1.h> 
//#include <d3dx11.h> 
#if !defined(__d3d11_h__) && !defined(__d3d11_x_h__) && !defined(__d3d12_h__) && !defined(__d3d12_x_h__)
#error include d3d11.h or d3d12.h before including TMath.h
#endif

#if !defined(_XBOX_ONE) || !defined(_TITLE)
//#include <dxgi1_2.h>
#endif

#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#ifndef XM_CONSTEXPR
#define XM_CONSTEXPR
#endif


struct Plane
{
	// 평면의 방정식
	// ax + by + cz + d = 0
	// normal = v0 cross v1 = (a, b, c)
	// d = -(ax + by + cz) = normal dot p0
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

class Frustum
{
public:
	Vector3f FrustumVertexList[8];
	Plane	FrustumPlane[6];

public:
	Matrix4x4 matView;
	Matrix4x4 matProj;

public:
	bool createFrustum(Matrix4x4* _view, Matrix4x4* _proj);
};