#pragma once
#include "Entity.hpp"
#include "Mesh.hpp"
#include "MovementComponent.h"

class Actor : public ECS::Entity
{
public:

public:
	Actor();
	virtual ~Actor();
};

Actor::Actor()
{
	this->AddComponent<MeshComponent>();
	this->AddComponent<MovementComponent>();
}

Actor::~Actor()
{

}