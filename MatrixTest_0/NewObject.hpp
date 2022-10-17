#pragma once
#include "Object.hpp"

class NewObject : public object2D<float>
{
public:
	void updateShader() override;
	void updateShaderCamera() override;
};

class BoxObject : public object2D<float>
{
public:
	Box_<float> box;

public:
	BoxObject() {};
	BoxObject(Box_<float>& _box)
	{
		box = _box;
	}

public:
	bool init();

public:
	void updateShader() override;
	void updateShaderCamera() override;
};