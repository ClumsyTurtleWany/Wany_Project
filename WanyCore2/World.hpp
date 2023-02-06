#pragma once
#include "ECSCommon.hpp"

namespace ECS
{
	class World
	{
	private:
		std::vector<std::shared_ptr<ECS::Entity>> Entities;
		std::vector<std::shared_ptr<ECS::System>> Systems;

	public:
		void Tick(float time);

		template<typename... Types>
		void each(typename)

	};
}