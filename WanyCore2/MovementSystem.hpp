#pragma once
#include "ECSCommon.hpp"
#include "System.hpp"

namespace ECS
{
	class MovementSystem : public ECS::System
	{
	public:
		virtual void Tick(World* world, float time) override;
	};
}