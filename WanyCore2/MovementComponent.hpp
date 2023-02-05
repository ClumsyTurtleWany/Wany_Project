#pragma once
#include "Vector.hpp"
#include "BaseComponent.hpp"

struct MovementComponent : public BaseComponent
{
	Vector3f	Location;
	Vector3f	Forward;
	float		Speed;

	MovementComponent() : Location({ 0.0, 0.0, 0.0 }), Forward({ 0.0, 0.0, 0.0 }), Speed(0) {};
	MovementComponent(Vector3f location, Vector3f forward, float speed) : Location(location), Forward(forward), Speed(speed) {};
};