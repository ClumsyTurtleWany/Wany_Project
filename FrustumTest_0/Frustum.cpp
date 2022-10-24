#include "Frustum.hpp"


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
	FrustumVertexList[0] = Vector3f(-1.0f, -1.0f, 1.0f);
	FrustumVertexList[1] = Vector3f(-1.0f,  1.0f, 1.0f);
	FrustumVertexList[2] = Vector3f( 1.0f,  1.0f, 1.0f);
	FrustumVertexList[3] = Vector3f( 1.0f, -1.0f, 1.0f);
	
	Matrix4x4 matInvViewProj = (*_view) * (*_proj);
	DirectX::XMMATRIX matSrc = *((DirectX::XMMATRIX*)&matInvViewProj);
	DirectX::XMMATRIX matDst = DirectX::XMMatrixInverse(nullptr, matSrc);

	Matrix4x4 matTemp = *((Matrix4x4*)&matDst);

	return false;
}
