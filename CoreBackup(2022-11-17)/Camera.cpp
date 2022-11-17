#include "Camera.hpp"
#include "Input.hpp"
#include "Timer.hpp"

Rect2f Camera::getRect()
{
	return rect;
}

Camera::Camera()
{
}

Camera::Camera(ProjectionType _type)
{
	projType = _type;
}

void Camera::setPos(const Vector2f& _pos)
{
	pos = _pos;
}

void Camera::setWidth(float _width)
{
	width = _width;
}

void Camera::setHeight(float _height)
{
	height = _height;
}

void Camera::setBoundary(const Rect2f& _boundaryRect)
{
	boundary = _boundaryRect;
}

Vector2f Camera::getPos()
{
	return pos;
}

float Camera::getWidth()
{
	return width;
}

float Camera::getHeight()
{
	return height;
}

Matrix4x4 Camera::getMatrix_View()
{
	return matView;
}

Matrix4x4 Camera::getMatrix_Projection()
{
	if (projType == ProjectionType::Perspective)
	{
		return matProj_Perspective;
	}
	else
	{
		return matProj_Orthogonal;
	}
}

void Camera::CreateMatrix_View(Vector3f _eye, Vector3f _target, Vector3f _up)
{
	cameraPos = _eye;
	look = _target;
	up = _up;

	Vector3f direction = (_target - _eye).normalized();
	Vector3f rightSide = up.cross(direction).normalized();
	Vector3f upSide = direction.cross(rightSide).normalized();

	matView._11 = rightSide.x; matView._12 = upSide.x; matView._13 = direction.x;
	matView._21 = rightSide.y; matView._22 = upSide.y; matView._23 = direction.y;
	matView._31 = rightSide.z; matView._32 = upSide.z; matView._33 = direction.z;
	matView._41 = -(cameraPos.x * matView._11 + cameraPos.y * matView._21 + cameraPos.z * matView._31);
	matView._42 = -(cameraPos.x * matView._12 + cameraPos.y * matView._22 + cameraPos.z * matView._32);
	matView._43 = -(cameraPos.x * matView._13 + cameraPos.y * matView._23 + cameraPos.z * matView._33);
	matView._14 = matView._24 = matView._34 = 0.0f;
	matView._44 = 1.0f;
}

void Camera::CreateMatrix_Proj(float _near, float _far, float _fov_y, float _aspect)
{
	nearDistance = _near;
	farDistance = _far;
	fov_y = _fov_y;
	aspectRatio = _aspect;

	if (projType == ProjectionType::Orthogonal)
	{
		if ((boundary.width() > rect.width()) || (boundary.height() > rect.height()))
		{
			// Orthogonal Projection Matrix
			float _11 = 2.0f / rect.width();
			float _22 = 2.0f / (rect.top() - rect.bottom());
			float _33 = 1.0f / (farDistance - nearDistance);
			float _41 = (rect.left() + rect.right()) / (rect.left() - rect.right());
			float _42 = (rect.top() + rect.bottom()) / (rect.left() - rect.right());
			float _43 = -nearDistance * _33;

			matProj_Orthogonal.Identity();
			matProj_Orthogonal._11 = _11;
			matProj_Orthogonal._22 = _22;
			matProj_Orthogonal._33 = _33;
			matProj_Orthogonal._41 = _41;
			matProj_Orthogonal._42 = _42;
			matProj_Orthogonal._43 = _43;
		}
		else
		{
			// Orthogonal Projection Matrix
			float _11 = 2.0f / rect.width();
			float _22 = 2.0f / rect.height();
			float _33 = 1.0f / (farDistance - nearDistance);
			float _43 = -nearDistance * _33;
		
			matProj_Orthogonal.Identity();
			matProj_Orthogonal._11 = _11;
			matProj_Orthogonal._22 = _22;
			matProj_Orthogonal._33 = _33;
			matProj_Orthogonal._34 = _43;
		}
	}

	// Perspective Projection Matrix
	float h = 1.0f / tan(fov_y * 0.5f);
	float w = h / aspectRatio;

	float Q = farDistance / (farDistance - nearDistance);

	matProj_Perspective._11 = w;
	matProj_Perspective._22 = h;
	matProj_Perspective._33 = Q;
	matProj_Perspective._43 = -Q * nearDistance;
	matProj_Perspective._34 = 1;
	matProj_Perspective._44 = 0.0f;
}

void Camera::update()
{
	right.x = matView._11;
	right.y = matView._21;
	right.z = matView._31;

	up.x = matView._12;
	up.y = matView._22;
	up.z = matView._32;

	look.x = matView._13;
	look.y = matView._23;
	look.z = matView._33;

	right = right.normalized();
	up = up.normalized();
	look = look.normalized();
}

bool Camera::initialize()
{
	return true;
}

bool Camera::frame()
{
	float x = pos.x - (width * 0.5f) < 0 ? 0 : pos.x - (width * 0.5f);
	float y = pos.y - (height * 0.5f) < 0 ? 0 : pos.y - (height * 0.5f);

	if (x + width > boundary.RB.x)
	{
		x = boundary.RB.x - width;
	}

	if (y + height > boundary.RB.y)
	{
		y = boundary.RB.y - height;
	}

	rect = Rect2f(x, y, width, height);	 

	/*float dt = Timer::getInstance()->getDeltaTime();

	KeyState KeyState_W = Input::getInstance()->getKey('W');
	if (KeyState_W == KeyState::Hold)
	{
		cameraPos.z += 10.0f * dt;
	}

	KeyState KeyState_S = Input::getInstance()->getKey('S');
	if (KeyState_S == KeyState::Hold)
	{
		cameraPos.z -= 10.0f * dt;
	}

	KeyState KeyState_A = Input::getInstance()->getKey('A');
	if (KeyState_A == KeyState::Hold)
	{
		cameraPos.x -= 10.0f * dt;
	}

	KeyState KeyState_D = Input::getInstance()->getKey('D');
	if (KeyState_D == KeyState::Hold)
	{
		cameraPos.x += 10.0f * dt;
	}

	KeyState KeyState_Q = Input::getInstance()->getKey('Q');
	if (KeyState_Q == KeyState::Hold)
	{
		cameraPos.y += 10.0f * dt;
	}

	KeyState KeyState_E = Input::getInstance()->getKey('E');
	if (KeyState_E == KeyState::Hold)
	{
		cameraPos.y -= 10.0f * dt;
	}*/

	CreateMatrix_View(cameraPos, look, up);
	update();

	return true;
}

bool Camera::render()
{
	return true;
}

bool Camera::release()
{
	return true;
}
