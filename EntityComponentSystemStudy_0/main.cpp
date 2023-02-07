#include <iostream>
#include "World.hpp"

void main()
{
	ECS::World* NewWorld = ECS::World::CreateWorld();

	NewWorld->Tick(10.0f);

	int a = 0;
}