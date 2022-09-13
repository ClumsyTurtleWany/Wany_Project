#include "Player.hpp"
#include "UserState_Idle.hpp"

Player::Player() : currentState(new UserState_Idle(this))
{
	pObj = new object2D<float>;
	pObj->createShader(ShaderType::Texture);
}

Player::Player(const Rect2f& _rect) : currentState(new UserState_Idle(this))
{
	pObj = new object2D<float>(_rect);
	pObj->createShader(ShaderType::Texture);
}

Player::~Player()
{
	release();
}

bool Player::initialize()
{
	return true;
}

bool Player::frame(float _dt)
{
	if (!pObj->frame(_dt))
	{
		return false;
	}

	if (!currentState->frame())
	{
		return false;
	}

	return true;
}

bool Player::render()
{
	if (!pObj->render())
	{
		return false;
	}

	if (!currentState->render())
	{
		return false;
	}

	return true;
}

bool Player::release()
{
	pObj->release();
	delete pObj;
	pObj = nullptr;
	return currentState->release();
}