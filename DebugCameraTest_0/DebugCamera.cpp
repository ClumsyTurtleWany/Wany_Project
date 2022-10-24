#include "DebugCamera.hpp"
#include "Input.hpp"
#include "Timer.hpp"

DebugCamera::DebugCamera()
{
}

DebugCamera::DebugCamera(ProjectionType _type)
{
	projType = _type;
}

bool DebugCamera::frame()
{
	float dt = Timer::getInstance()->getDeltaTime();

	KeyState keyState_LButton = Input::getInstance()->getKey(VK_LBUTTON);
	if (keyState_LButton == KeyState::Hold)
	{
		POINT ptOffset = Input::getInstance()->m_ptOffset;
		yaw += ptOffset.x * dt;
		pitch += ptOffset.y * dt;
	}

	KeyState keyState_Space = Input::getInstance()->getKey(VK_SPACE);
	if (keyState_Space == KeyState::Hold)
	{
		speed = 100.0f;
	}
	else
	{
		speed = 50.0f;
	}

	KeyState KeyState_W = Input::getInstance()->getKey('W');
	if (KeyState_W == KeyState::Hold)
	{
		cameraPos += look * speed * dt;
	}

	KeyState KeyState_S = Input::getInstance()->getKey('S');
	if (KeyState_S == KeyState::Hold)
	{
		cameraPos -= look * speed * dt;
	}

	KeyState KeyState_A = Input::getInstance()->getKey('A');
	if (KeyState_A == KeyState::Hold)
	{
		cameraPos -= right * speed * dt;
	}

	KeyState KeyState_D = Input::getInstance()->getKey('D');
	if (KeyState_D == KeyState::Hold)
	{
		cameraPos += right * speed * dt;
	}

	KeyState KeyState_Q = Input::getInstance()->getKey('Q');
	if (KeyState_Q == KeyState::Hold)
	{
		cameraPos += up * speed * dt;
	}

	KeyState KeyState_E = Input::getInstance()->getKey('E');
	if (KeyState_E == KeyState::Hold)
	{
		cameraPos -= up * speed * dt;
	}

	DirectX::XMFLOAT3 curPos;
	curPos.x = cameraPos.x;
	curPos.y = cameraPos.y;
	curPos.z = cameraPos.z;

	//////////////////////////// DebugCamera ////////////////////////////
	
	DirectX::XMVECTOR quaternion = DirectX::XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
	DirectX::XMMATRIX world = DirectX::XMMatrixAffineTransformation({ 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, quaternion, DirectX::XMLoadFloat3(&curPos));
	DirectX::XMVECTOR determinant;
	DirectX::XMMATRIX view = DirectX::XMMatrixInverse(&determinant, world);
	
	matView = *((Matrix4x4*)&view);

	update();
	return true;
}
