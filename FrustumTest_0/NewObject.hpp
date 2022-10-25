#pragma once
#include "Object.hpp"

#include <d3d11_1.h> 
//#include <d3dx11.h> 
#if !defined(__d3d11_h__) && !defined(__d3d11_x_h__) && !defined(__d3d12_h__) && !defined(__d3d12_x_h__)
#error include d3d11.h or d3d12.h before including TMath.h
#endif

#if !defined(_XBOX_ONE) || !defined(_TITLE)
//#include <dxgi1_2.h>
#endif

#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#ifndef XM_CONSTEXPR
#define XM_CONSTEXPR
#endif

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
	Vector3f curPos;

public:
	virtual bool initialize() override;
	virtual bool initializeVertexList() override;
	virtual bool initializeIndexList() override;
	virtual bool render() override;
	virtual bool frame(float _dt) override;
};

class Cube3D : public object3D<float>
{
private:
	Axis3D axis;

public:
	float testTime = 0.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;
	Vector3f curPos;

public:
	virtual bool initialize() override;
	virtual bool initializeVertexList() override;
	virtual bool initializeIndexList() override;
	virtual bool render() override;
	virtual bool frame(float _dt) override;

public:
	virtual bool rotationYawPitchRoll(float _yaw, float _pitch, float _roll);
};

class Map3D : public object3D<float>
{
private:
	Axis3D axis;

public:
	int width = 0;
	int height = 0;
	Vector3f curPos;

public:
	virtual bool render() override;
	virtual bool frame(float _dt) override;

public:
	bool build(int _width, int _height);	
};