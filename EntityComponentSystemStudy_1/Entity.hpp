#pragma once
#include "ECSCommon.hpp"
#include "Component.hpp"

// https://youtu.be/sl-_kgkuCy8

namespace ECS
{
	class Entity
	{
	private:
		std::unordered_map<ComponentID, std::shared_ptr<ECS::Component>> Components;
		int ID;

	public:
		Entity() {};
		virtual ~Entity() {};

	public:

		template<typename ComponentType, typename... ComponentArgs>
		ComponentType* AddComponent(ComponentArgs&&... args)
		{
			ComponentID id = ECS::GetComponentID<ComponentType>();
			auto it = Components.find(id);
			if (it != Components.end())
			{
				ComponentContainer<ComponentType>* container = reinterpret_cast<ComponentContainer<ComponentType>*>(it->second.get());
				container->Data = ComponentType(args...);
				
				return &container->Data;
			}
			else
			{
				ComponentContainer<ComponentType>* container = new ComponentContainer<ComponentType>();
				container->Data = ComponentType(args...);
				std::shared_ptr<ComponentContainer<ComponentType>> newComp(container);
				Components.insert(std::make_pair(id, newComp));

				return &container->Data;
			}
			
		}

		template<typename ComponentType>
		ComponentType* GetComponent()
		{
			ComponentID id = ECS::GetComponentID<ComponentType>();
			auto it = Components.find(id);
			if (it == Components.end())
			{
				return nullptr;
			}

			ComponentContainer<ComponentType>* container = reinterpret_cast<ComponentContainer<ComponentType>*>(it->second.get());
			return &container->Data;
		}

		template<typename ComponentType>
		bool RemoveComponent()
		{
			ComponentID id = ECS::GetComponentID<ComponentType>();
			auto it = Components.find(id);
			if (it != Components.end())
			{
				Components.erase(it);
				return true;
			}

			return false;
		}
	};
}