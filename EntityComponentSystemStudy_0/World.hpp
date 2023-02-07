#pragma once
#include "ECSCommon.hpp"
#include "System.hpp"

namespace ECS
{
	class World
	{
	private:
		std::vector<std::shared_ptr<ECS::Entity>> Entities;
		std::vector<std::shared_ptr<ECS::System>> Systems;

	public:
		static World* CreateWorld();
		void Tick(float time);
		void AddEntity(Entity* entity);
	};

	inline World* World::CreateWorld()
	{
		std::shared_ptr<World> NewWorld = std::make_shared<World>();
		return NewWorld.get();
	}

	void World::Tick(float time)
	{
		for (auto system : Systems)
		{
			system.get()->Tick(this, time);
		}
	}
	inline void World::AddEntity(Entity* entity)
	{
		Entities.push_back(std::make_shared<Entity>(entity));
	}
}