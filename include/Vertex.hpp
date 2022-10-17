#pragma once
#include "Vector.hpp"

// Vertex�� ���� p(��ġ), n(�븻), c(����), t(�ؽ�ó)�� �����ȴ�.

struct Vertex
{
	// Position
	Vector3f pos;

	// Color
	Vector4f color;

	// Texture
	Vector2f texture;

	Vertex() {};
	Vertex(const Vector3f& _pos, const Vector4f& _color, const Vector2f& _texture)
	{
		pos = _pos;
		color = _color;
		texture = _texture;
	}
};