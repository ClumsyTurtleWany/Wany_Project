#pragma once
#include "Define.hpp"

struct Material
{
	ID3D11VertexShader*		VertexShader = nullptr;
	ID3D11PixelShader*		PixelShader = nullptr;
	ID3D11Buffer*			ConstantBuffer = nullptr;
	ConstantBufferData		ConstantBufData;
	std::vector<DXTexture>	Textures;
};

struct MeshComponent
{
public:
	std::vector<Vertex> Vertices;
	std::vector<DWORD>	Indeices;
	Material			Material;

public:
	MeshComponent() {};
};

struct StaticMesh
{
public:
	std::vector<MeshComponent> Meshes;

public:
	StaticMesh() {};
};

struct SkeletalMesh
{
public:
	std::vector<MeshComponent> Meshes;

public:
	SkeletalMesh() {};
};