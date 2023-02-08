#pragma once
#include "ECSCommon.hpp"
#include "Component.hpp"

namespace ECS
{
	class Entity
	{
	private:
		std::unordered_map<ComponentID, std::shared_ptr<ECS::Component>> Components;
		int ID;

	public:

		template<typename ComponentType, typename... ComponentArgs>
		ComponentType* AddComponent(ComponentArgs&&... args)
		{
			ComponentID id = GetComponentID<ComponentType>();
			auto it = Components.find(id);
			if (it != Components.end())
			{
				it->second.reset(new ComponentType(args...));
				return (ComponentType*)it->second.get();
			}
			else
			{
				std::shared_ptr<ComponentType> newComp(new ComponentType(args...));
				Components.insert(id, newComp);

				return (ComponentType*)newComp.get();
			}
		}
	};
}