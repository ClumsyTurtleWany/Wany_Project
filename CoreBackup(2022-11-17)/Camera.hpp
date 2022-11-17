#pragma once
#include "Define.hpp"

enum class ProjectionType
{
	Orthogonal,
	Perspective,
};

class Camera //: public Singleton<Camera>
{
private:
	//friend class Singleton<DXShaderBorderManager>;

	Vector2f pos;
	float width = 0.0f;
	float height = 0.0f;
	Rect2f rect;
	Rect2f boundary;

public:
	float farDistance = 0.0f;
	float nearDistance = 0.0f;
	float aspectRatio = 0.0f;
	float fov_x = 0.0f;
	float fov_y = 0.0f;

	Vector3f cameraPos;
	Vector3f look = { 0, 0, 0 };
	Vector3f right = { 1, 0, 0 };
	Vector3f up = { 0, 1, 0 };

	Matrix4x4 matView;
	Matrix4x4 matProj_Perspective;
	Matrix4x4 matProj_Orthogonal;
	ProjectionType projType = ProjectionType::Perspective;

public:
	Camera();
	Camera(ProjectionType _type);
	
public:
	void setPos(const Vector2f& _pos);
	//void setCameraPos(const Vector3f& _pos);
	void setWidth(float _width);
	void setHeight(float _height);
	void setBoundary(const Rect2f& _boundaryRect);

	Rect2f getRect();
	Vector2f getPos();
	float getWidth();
	float getHeight();
	Matrix4x4 getMatrix_View();
	Matrix4x4 getMatrix_Projection();

	virtual void CreateMatrix_View(Vector3f _eye, Vector3f _target, Vector3f _up);
	virtual void CreateMatrix_Proj(float _near, float _far, float _fov_y, float _aspect);
	virtual void update();

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};