#include "pch.h"
#include "Frustum.hpp"
#include "DXMath.hpp"

//https://docs.microsoft.com/en-us/windows/win32/dxmath/pg-xnamath-migration-d3dx
bool Frustum::createFrustum(Matrix4x4* _view, Matrix4x4* _proj)
{
	// v' = v * world * view * proj;
	// Frustum = v * world * view * proj * proj^inv * view^inv = ;
	// v' /= v'.w   =>  x,y = -1 ~ +1, z = 0 ~ 1
	FrustumVertexList[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	FrustumVertexList[1] = Vector3f(-1.0f,  1.0f, 0.0f);
	FrustumVertexList[2] = Vector3f( 1.0f,  1.0f, 0.0f);
	FrustumVertexList[3] = Vector3f( 1.0f, -1.0f, 0.0f);
	FrustumVertexList[4] = Vector3f(-1.0f, -1.0f, 1.0f);
	FrustumVertexList[5] = Vector3f(-1.0f,  1.0f, 1.0f);
	FrustumVertexList[6] = Vector3f( 1.0f,  1.0f, 1.0f);
	FrustumVertexList[7] = Vector3f( 1.0f, -1.0f, 1.0f);
	// 5 6
	// 4 7
	// 1 2
	// 0 3
	
	Matrix4x4 matViewProj = (*_view) * (*_proj);
	Matrix4x4 matInv = MakeInversedMatrix(matViewProj);
	for (int idx = 0; idx < 8; idx++)
	{
		FrustumVertexList[idx] = FrustumVertexList[idx] * matInv;
	}

	// Frustum 단면을 생성 할 때 근단면으로 돌리면 오차가 나올 확률이 높다. 
	// (근단면의 경우 distance를 0.1을 넣는 경우도 있어 폭이 매우 좁아 오차 발생 가능성이 높다.)
	// 따라서 원단면을 베이스로 하는것이 좋다.(원단면 정점 2개 + 근단면 정점 1개로 평면 생성)
	// front
	FrustumPlane[0].create(FrustumVertexList[2], FrustumVertexList[1], FrustumVertexList[0]);
	// left
	FrustumPlane[1].create(FrustumVertexList[5], FrustumVertexList[4], FrustumVertexList[1]);
	// right
	FrustumPlane[2].create(FrustumVertexList[7], FrustumVertexList[6], FrustumVertexList[2]);
	// back
	FrustumPlane[3].create(FrustumVertexList[4], FrustumVertexList[5], FrustumVertexList[6]);
	// top
	FrustumPlane[4].create(FrustumVertexList[6], FrustumVertexList[5], FrustumVertexList[1]);
	// bottom
	FrustumPlane[5].create(FrustumVertexList[4], FrustumVertexList[7], FrustumVertexList[0]);


	std::vector<Vertex> VertexList;
	VertexList.resize(8);
	VertexList[0] = Vertex(Vector3f(FrustumVertexList[0]), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[1] = Vertex(Vector3f(FrustumVertexList[1]), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[2] = Vertex(Vector3f(FrustumVertexList[2]), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[3] = Vertex(Vector3f(FrustumVertexList[3]), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[4] = Vertex(Vector3f(FrustumVertexList[4]), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[5] = Vertex(Vector3f(FrustumVertexList[5]), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[6] = Vertex(Vector3f(FrustumVertexList[6]), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[7] = Vertex(Vector3f(FrustumVertexList[7]), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));

	pShader->updateVertexList(&VertexList);

	std::vector<DWORD> IndexList;
	IndexList.resize(24);
	size_t idx = 0;
	IndexList[idx++] = 0;
	IndexList[idx++] = 1;
	IndexList[idx++] = 1;
	IndexList[idx++] = 2;
	IndexList[idx++] = 2;
	IndexList[idx++] = 3;
	IndexList[idx++] = 3;
	IndexList[idx++] = 0;

	IndexList[idx++] = 4;
	IndexList[idx++] = 5;
	IndexList[idx++] = 5;
	IndexList[idx++] = 6;
	IndexList[idx++] = 6;
	IndexList[idx++] = 7;
	IndexList[idx++] = 7;
	IndexList[idx++] = 4;

	IndexList[idx++] = 1;
	IndexList[idx++] = 5;
	IndexList[idx++] = 2;
	IndexList[idx++] = 6;
	IndexList[idx++] = 0;
	IndexList[idx++] = 4;
	IndexList[idx++] = 3;
	IndexList[idx++] = 7;

	pShader->updateIndexList(&IndexList);

	data.matView = (*_view);
	data.matProj = (*_proj);

	return true;
}

bool Frustum::classifyPoint(Vector3f _pos)
{
	for (int idx = 0; idx < 6; idx++)
	{
		Vector3f normal = Vector3f(FrustumPlane[idx].a, FrustumPlane[idx].b, FrustumPlane[idx].c);
		float h = normal.dot(_pos) + FrustumPlane[idx].d;
		if (h < 0)
		{
			return false;
		}
	}
	return true;
}

bool Frustum::initialize()
{
	pShader->setTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	return true;
}

bool Frustum::render()
{
	pShader->render();
	return true;
}
