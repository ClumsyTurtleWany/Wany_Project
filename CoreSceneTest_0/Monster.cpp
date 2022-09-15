#include "Monster.hpp"
#include "UserState_Idle.hpp"

Monster::Monster()// : currentState(new UserState_Idle(this))
{
	pObj = new object2D<float>;
	pObj->type = OBJECT_TYPE::DYNAMIC_OBJECT;
	pObj->createShader(ShaderType::Normal);
}

Monster::Monster(const Rect2f& _rect)// : currentState(new UserState_Idle(this))
{
	pObj = new object2D<float>(_rect);
	pObj->type = OBJECT_TYPE::DYNAMIC_OBJECT;
	pObj->createShader(ShaderType::Normal);
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
	if (!pObj->frame(_dt))
	{
		return false;
	}

	/*if (!currentState->frame())
	{
		return false;
	}*/

	pObj->hitbox = pObj->shape;

	return true;
}

bool Monster::render()
{
	if (!pObj->render())
	{
		return false;
	}

	//DrawBorder(pObj->hitbox, BORDER_COLOR_RED);

	/*if (!currentState->render())
	{
		return false;
	}*/

	return true;
}

bool Monster::release()
{
	pObj->release();
	delete pObj;
	pObj = nullptr;
	return true; // currentState->release();
}