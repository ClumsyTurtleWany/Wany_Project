#include <iostream>
#include "World.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "Entity.hpp"

class Movement : public ECS::Component
{
public:
	float _a;
	float _b;
	float _c;

public:
	Movement() : _a(0.0f), _b(0.0f), _c(0.0f) {};
	Movement(float a, float b, float c) : _a(a), _b(b), _c(c) {};
};

class MovementSystem : public ECS::System
{
public:
	virtual void Tick(ECS::World* world, float time) override
	{
		
	}

};

class Actor : public ECS::Entity
{

};

int main()
{
	ECS::World* NewWorld = ECS::World::CreateWorld();

	std::shared_ptr<Actor> newActor = std::make_shared<Actor>();
	newActor.get()->AddComponent<Movement>(10.0, 20.0, 30.0);

	NewWorld->Tick(10.0f);

	int a = 0;

	return 0;
}