#pragma once
#include "Define.hpp"

struct Material
{

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