#pragma once
#include "Vector.hpp"

// Vertex는 보통 p(위치), n(노말), c(색상), t(텍스처)로 구성된다.

struct Vertex
{
	// Position
	Vector3f pos;

	// Normal
	Vector3f normal;

	// Color
	Vector4f color;

	// Texture
	Vector2f texture;

	Vertex() {};
	Vertex(const Vector3f& _pos, const Vector4f& _color, const Vector2f& _texture)
	{
		pos = _pos;
		normal = Vector3f(0.0f, 0.0f, 0.0f);
		color = _color;
		texture = _texture;
	}

	Vertex(const Vector3f& _pos, const Vector3f& _normal, const Vector4f& _color, const Vector2f& _texture)
	{
		pos = _pos;
		normal = _normal;
		color = _color;
		texture = _texture;
	}
};