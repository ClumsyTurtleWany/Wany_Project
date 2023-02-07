#pragma once
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <functional>

namespace ECS
{
	template <typename T>
	std::type_index GetTypeIndex()
	{
		return std::type_index(typeid(T));
	}

	class World;
	class Entity;
	class Component;
	class System;

}