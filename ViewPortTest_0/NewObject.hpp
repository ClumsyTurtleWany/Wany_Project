#pragma once
#include "Object.hpp"

class Axis3D : public object3D<float>
{
private:
	Vector3f AxisSize;

private:
	virtual bool initializeVertexList() override;
	virtual bool initializeIndexList() override;

public:
	virtual bool initialize() override;

public:
	void setAxisSize(float _x, float _y, float _z);
};

class Plane3D : public object3D<float>
{
private:
	Axis3D axis;

public:
	float testTime = 0.0f;

public:
	virtual bool initialize() override;
	virtual bool initializeVertexList() override;
	virtual bool initializeIndexList() override;
	virtual bool render() override;
};

class Cube3D : public object3D<float>
{
private:
	Axis3D axis;

public:
	float testTime = 0.0f;

public:
	virtual bool initialize() override;
	virtual bool initializeVertexList() override;
	virtual bool initializeIndexList() override;
	virtual bool render() override;
};

class Map3D : public object3D<float>
{
private:
	Axis3D axis;

public:
	int width = 0.0f;
	int height = 0.0f;

public:
	virtual bool render() override;

public:
	bool build(int _width, int _height);	
};