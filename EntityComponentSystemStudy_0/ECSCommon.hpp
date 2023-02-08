#pragma once
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <functional>
#include <bitset>
#include <array>

namespace ECS
{
	class World;
	class Entity;
	class Component;
	class System;

	using ComponentID = std::type_index;

	template <typename T>
	ComponentID GetComponentID()
	{
		return ComponentID(typeid(T));
	}

}