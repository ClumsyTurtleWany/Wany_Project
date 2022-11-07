#pragma once
#ifndef __DX_MATH__
#define __DX_MATH__

#include <math.h>
#include <vector>
#include "Vector.hpp"

#include <d3d11_1.h> 
#include <DirectXMath.h>

inline DirectX::XMMATRIX toXMMatrix(const Matrix4x4& _mat)
{
	DirectX::XMMATRIX rst = *((DirectX::XMMATRIX*)&_mat);
	return rst;
}

inline Matrix4x4 toMatrix(const DirectX::XMMATRIX& _mat)
{
	Matrix4x4 rst = *((Matrix4x4*)&_mat);
	return rst;
}

inline Matrix4x4 MakeInversedMatrix(const Matrix4x4& _mat)
{
	DirectX::XMMATRIX src = toXMMatrix(_mat);
	DirectX::XMMATRIX temp = DirectX::XMMatrixInverse(nullptr, src);
	Matrix4x4 rst = toMatrix(temp);
	return rst;
}

inline Matrix4x4 MakeInversedMatrix(const DirectX::XMMATRIX& _mat)
{
	DirectX::XMMATRIX temp = DirectX::XMMatrixInverse(nullptr, _mat);
	Matrix4x4 rst = toMatrix(temp);
	return rst;
}

inline DirectX::XMVECTOR Vector3fToXMVector(const Vector3f& _vec)
{
	DirectX::XMFLOAT3 temp;
	temp.x = _vec.x;
	temp.y = _vec.y;
	temp.z = _vec.z;
	DirectX::XMVECTOR rst = DirectX::XMLoadFloat3(&temp);
	return rst;
}

inline DirectX::XMVECTOR Vector4fToXMVector(const Vector4f& _vec)
{
	DirectX::XMFLOAT4 temp;
	temp.x = _vec.x;
	temp.y = _vec.y;
	temp.z = _vec.z;
	temp.w = _vec.w;
	DirectX::XMVECTOR rst = DirectX::XMLoadFloat4(&temp);
	return rst;
}

inline Vector3f toVector3f(const DirectX::XMVECTOR& _vec)
{
	Vector3f rst;
	rst.x = DirectX::XMVectorGetX(_vec);
	rst.y = DirectX::XMVectorGetY(_vec);
	rst.z = DirectX::XMVectorGetZ(_vec);
	return rst;
}

inline Vector4f toVector4f(const DirectX::XMVECTOR& _vec)
{
	Vector4f rst;
	rst.x = DirectX::XMVectorGetX(_vec);
	rst.y = DirectX::XMVectorGetY(_vec);
	rst.z = DirectX::XMVectorGetZ(_vec);
	rst.w = DirectX::XMVectorGetW(_vec);
	return rst;
}

#endif