#include "World.hpp"
#include "System.hpp"

void ECS::World::Tick(float time)
{
	for (auto system : Systems)
	{
		system.get()->Tick(this, time);
	}
}
