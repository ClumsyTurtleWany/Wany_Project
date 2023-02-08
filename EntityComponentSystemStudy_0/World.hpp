#pragma once
#include "ECSCommon.hpp"
#include "System.hpp"
#include "Entity.hpp"

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

		template <typename... T>
		void GetEntities(std::vector<ECS::Entity>& entities);
	};

	inline World* World::CreateWorld()
	{
		std::shared_ptr<World> NewWorld = std::make_shared<World>();
		return NewWorld.get();
	}

	void World::Tick(float time)
	{
		for (auto& system : Systems)
		{
			system.get()->Tick(this, time);
		}
	}

	inline void World::AddEntity(Entity* entity)
	{
		std::shared_ptr<Entity> newEntity(entity);
		Entities.push_back(newEntity);
	}


	template<typename ...T>
	inline void World::GetEntities(std::vector<ECS::Entity>& entities)
	{

	}

}