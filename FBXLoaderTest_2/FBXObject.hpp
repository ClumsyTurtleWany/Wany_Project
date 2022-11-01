#pragma once
#include "Object.hpp"
#include "NewObject.hpp"

class FBXObject : public object3D<float>
{
private:
	Axis3D axis;

public:
	float testTime = 0.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;
	Vector3f curPos;

	std::vector<FBXObject*> child;
	std::vector<DXShader*> Materials;

public:
	virtual bool initialize() override;
	virtual bool initializeVertexList() override;
	virtual bool initializeIndexList() override;
	virtual bool render() override;
	virtual bool frame(float _dt) override;
	virtual bool setMatrix(Matrix4x4* _world, Matrix4x4* _view, Matrix4x4* _proj) override;

public:
	virtual bool rotationYawPitchRoll(float _yaw, float _pitch, float _roll);

};