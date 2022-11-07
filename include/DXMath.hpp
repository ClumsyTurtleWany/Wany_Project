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

inline bool Matrix4x4Decompose(Matrix4x4& _src, Vector3f& _scale, Vector4f& _rotation, Vector3f& _translation)
{
	DirectX::XMVECTOR s, r, t;

	if (!DirectX::XMMatrixDecompose(&s, &r, &t, toXMMatrix(_src)))
	{
		return false;
	}

	_scale = toVector3f(s);
	_rotation = toVector4f(r);
	_translation = toVector3f(t);

	return true;
}

// (Vector3f) Linear Interpolation
inline Vector3f Vector3fLerp(const Vector3f& _v1, const Vector3f& _v2, float _t)
{
	DirectX::XMVECTOR v1 = Vector3fToXMVector(_v1);
	DirectX::XMVECTOR v2 = Vector3fToXMVector(_v2);
	DirectX::XMVECTOR rst = DirectX::XMVectorLerp(v1, v2, _t);
	return toVector3f(rst);
}

// (Quaternion) Linear Interpolation
inline Vector4f QuaternionLerp(const Vector4f& _v1, const Vector4f& _v2, float _t)
{
	DirectX::XMVECTOR v1 = Vector4fToXMVector(_v1);
	DirectX::XMVECTOR v2 = Vector4fToXMVector(_v2);
	DirectX::XMVECTOR rst = DirectX::XMQuaternionSlerp(v1, v2, _t);
	return toVector4f(rst);
}

inline Matrix4x4 QuaternionToMatrix4x4(const Vector4f& _v)
{
	DirectX::XMVECTOR v = Vector4fToXMVector(_v);
	DirectX::XMMATRIX rst = DirectX::XMMatrixRotationQuaternion(v);
	return toMatrix(rst);
}

#endif