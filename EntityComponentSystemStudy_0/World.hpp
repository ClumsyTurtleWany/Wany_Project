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
		std::vector<std::shared_ptr<ECS::System>> DisableSystems;

	public:
		//---------------------------------------------
		// Common
		//---------------------------------------------
		void Tick(float time);

		//---------------------------------------------
		// Entity
		//---------------------------------------------
		void AddEntity(Entity* entity);
		std::vector<std::shared_ptr<ECS::Entity>>& GetEntities();

		//---------------------------------------------
		// System
		//---------------------------------------------
		System* AddSystem(System* system);
		void EnableSystem(System* system);
		void DisableSystem(System* system);
	};

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

	std::vector<std::shared_ptr<ECS::Entity>>& World::GetEntities()
	{
		return Entities;
	}

	System* World::AddSystem(System* system)
	{
		std::shared_ptr<System> newSystem(system);
		Systems.push_back(newSystem);
		return system;
	}

	void World::EnableSystem(System* system)
	{
		std::shared_ptr<System> enableSystem(system);
		auto it = std::find(DisableSystems.begin(), DisableSystems.end(), enableSystem);
		if (it != DisableSystems.end())
		{
			DisableSystems.erase(it);
			Systems.push_back(enableSystem);
		}
	}

	void World::DisableSystem(System* system)
	{
		std::shared_ptr<System> disableSystem(system);
		auto it = std::find(Systems.begin(), Systems.end(), disableSystem);
		if (it != Systems.end())
		{
			Systems.erase(it);
			DisableSystems.push_back(disableSystem);
		}
	}

}