#pragma once
#include "Define.hpp"
#include "System.hpp"
#include "World.hpp"
#include "Mesh.hpp"

class RenderSystem : public ECS::System
{
public:
	virtual void Tick(ECS::World* world, float time) override
	{
		for (auto& entity : world->GetEntities())
		{
			bool isRender = false;
			auto staticMesh = entity.get()->GetComponent<StaticMesh>();
			if (staticMesh)
			{
				isRender = false;
			}
			else
			{
				auto skeletalMesh = entity.get()->GetComponent<SkeletalMesh>();
			}
			
		}
	}
};