#include <iostream>
#include "World.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "Entity.hpp"

class Movement
{
public:
	float _a;
	float _b;
	float _c;

public:
	Movement() : _a(0.0f), _b(0.0f), _c(0.0f) {};
	Movement(float a, float b, float c) : _a(a), _b(b), _c(c) {};
};

//ECS_DEFINE_TYPE(Movement)

class MovementSystem : public ECS::System
{
public:
	virtual void Tick(ECS::World* world, float time) override
	{
		for (auto& entity : world->GetEntities())
		{
			auto movement = entity.get()->GetComponent<Movement>();
			if (!movement)
			{
				continue;
			}

			movement->_a += 10;
		}
	}

};

class Actor : public ECS::Entity
{
public:
	Actor();
	virtual ~Actor();
};

int main()
{
	ECS::World* NewWorld = new ECS::World();

	std::shared_ptr<Actor> newActor = std::make_shared<Actor>();
	//auto it = newActor.get()->AddComponent<Movement>(10.0, 20.0, 30.0);
	//auto it2 = newActor.get()->AddComponent<Movement>(40.0, 50.0, 60.0);

	auto comp = newActor.get()->GetComponent<Movement>();
	comp->_a = 100;
	comp->_b = 200;
	comp->_c = 300;

	auto comp2 = newActor.get()->GetComponent<Movement>();

	NewWorld->AddSystem(new MovementSystem());

	NewWorld->AddEntity(newActor.get());

	NewWorld->Tick(10.0f);

	delete NewWorld;
	int a = 0;

	return 0;
}

Actor::Actor()
{
	this->AddComponent<Movement>(10.0, 20.0, 30.0);
	this->AddComponent<Movement>(40.0, 50.0, 60.0);
}

Actor::~Actor()
{
}
