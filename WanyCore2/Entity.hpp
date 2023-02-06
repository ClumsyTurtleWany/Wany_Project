#pragma once
#include "ECSCommon.hpp"

namespace ECS
{
	class Entity
	{
	private:
		std::unordered_map<std::type_index, ECS::Component> Components;
		int ID;
	};
}