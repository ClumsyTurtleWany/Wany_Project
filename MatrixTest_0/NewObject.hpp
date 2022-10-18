#pragma once
#include "Object.hpp"

class NewObject : public object2D<float>
{
public:
	ConstantBufferData data;

public:
	void updateShader() override;
	void updateShaderCamera() override;

	bool setMatrix(Matrix4x4 _world, Matrix4x4 _view, Matrix4x4 _proj);

public:
	bool render() override;
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
	bool initVertex();
	bool setMatrix(Matrix4x4 _world, Matrix4x4 _view, Matrix4x4 _proj);

public:
	void updateShader() override;
	void updateShaderCamera() override;


};

class Map : public object2D<float>
{
public:
	bool build(int _width, int _height);
};