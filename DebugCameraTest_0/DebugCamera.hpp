#pragma once
#include "Camera.hpp"
#include "Frustum.hpp"

class DebugCamera : public Camera
{
public:
	float speed = 10.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;

public:
	DebugCamera();
	DebugCamera(ProjectionType _type);

public:
	virtual bool frame() override;
};