#pragma once
#include "Vector.hpp"

// Vertex�� ���� p(��ġ), n(�븻), c(����), t(�ؽ�ó)�� �����ȴ�.

struct Vertex
{
	// Position
	Vector3f Coord;

	// Normal
	Vector3f Normal;

	// Color
	Vector4f Color;

	// Texture
	Vector3f UV;

	Vertex() {};
	Vertex(const Vector3f& _coord, const Vector4f& _color, const Vector3f& _uv)
	{
		Coord = _coord;
		Normal = Vector3f(0.0f, 0.0f, 0.0f);
		Color = _color;
		UV = _uv;
	}

	Vertex(const Vector3f& _coord, const Vector3f& _normal, const Vector4f& _color, const Vector3f& _uv)
	{
		Coord = _coord;
		Normal = _normal;
		Color = _color;
		UV = _uv;
	}
};
