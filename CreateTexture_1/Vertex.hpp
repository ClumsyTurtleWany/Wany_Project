#pragma once
#include "Vector.hpp"

// Vertex는 보통 p(위치), n(노말), c(색상), t(텍스처)로 구성된다.

struct Vertex
{
	// Position
	Vector3f pos;

	// Color
	Vector4f color;

	// Texture
	Vector2f texture;
};