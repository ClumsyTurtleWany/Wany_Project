#include "Player.hpp"
#include "UserState_Idle.hpp"

Player::Player() : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>;
	//pObj->createShader(ShaderType::Texture);
	mass = 1.0f;
}

Player::Player(const Rect2f& _rect) : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>(_rect);
	//pObj->createShader(ShaderType::Texture);
	mass = 1.0f;
	shape = _rect;
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
	object2D<float>::frame(_dt);
	/*if (!pObj->frame(_dt))
	{
		return false;
	}*/

	if (!currentState->frame())
	{
		return false;
	}

	//accel = force / mass;
	//velocity += accel * _dt;
	//velocity = accel * _dt;
	//Vector2f distance = velocity * _dt;
	//shape.offset(distance);

	Vector2f distance = force * _dt;
	shape.offset(distance);

	if (shape.LT.x < 0)
	{
		Rect2f rectTemp = shape;
		float width = rectTemp.width();
		shape.LT.x = 0;
		shape.RB.x = shape.LT.x + width - 1;
	}

	if (shape.LT.y < 0)
	{
		Rect2f rectTemp = shape;
		shape.LT.y = 0;
		shape.RB.y = shape.LT.y + rectTemp.height() - 1;
	}

	if (shape.RB.x > mapWidth)
	{
		Rect2f rectTemp = shape;
		shape.RB.x = mapWidth;
		shape.LT.x = shape.RB.x - rectTemp.width() + 1;
	}

	if (shape.RB.y > mapHeight)
	{
		Rect2f rectTemp = shape;
		shape.RB.y = mapHeight;
		shape.LT.y = shape.RB.y - rectTemp.height() + 1;
	}

	//renderCamera->setPos(shape.center());
	//pObj->hitbox = pObj->shape;
	hitbox = shape;

	return true;
}

bool Player::render()
{
	object2D<float>::render();
	/*if (!pObj->render())
	{
		return false;
	}*/

	DrawBorder(hitbox, BORDER_COLOR_RED);

	if (!currentState->render())
	{
		return false;
	}

	//DrawBorder(hitbox, BORDER_COLOR_RED);

	return true;
}

bool Player::release()
{
	//pObj->release();
	//delete pObj;
	//pObj = nullptr;
	return currentState->release();
}

void Player::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

Rect2f Player::getRect()
{
	return shape;
}

Vector2f Player::getCenter()
{
	return shape.center();
}
