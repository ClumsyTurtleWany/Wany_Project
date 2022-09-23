#include "Monster.hpp"
#include "UserState_Idle.hpp"

Monster::Monster()// : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>;
	type = OBJECT_TYPE::DYNAMIC_OBJECT;
	createShader(ShaderType::Normal);
}

Monster::Monster(const Rect2f& _rect)// : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>(_rect);
	type = OBJECT_TYPE::DYNAMIC_OBJECT;
	createShader(ShaderType::Normal);
}

Monster::~Monster()
{
	release();
}

bool Monster::initialize()
{
	return true;
}

bool Monster::frame(float _dt)
{
	if (!object2D<float>::frame(_dt))
	{
		return false;
	}

	/*if (!currentState->frame())
	{
		return false;
	}*/

	hitbox = shape;

	return true;
}

bool Monster::render()
{
	if (!object2D<float>::render())
	{
		return false;
	}

	DrawBorder(hitbox, BORDER_COLOR_RED);

	/*if (!currentState->render())
	{
		return false;
	}*/

	return true;
}

bool Monster::release()
{
	return true; // currentState->release();
}