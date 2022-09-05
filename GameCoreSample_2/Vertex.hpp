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
};