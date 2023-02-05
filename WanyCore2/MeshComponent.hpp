#pragma once
#include "Vertex.h"
#include "BaseComponent.hpp"

struct Material : public BaseComponent
{

};

struct Mesh : public BaseComponent
{
	std::vector<Vertex> Vertices;
	Material			MaterialSlot;
};

struct StaticMesh : public Mesh
{

};

struct SkeletalMesh : public Mesh
{

};