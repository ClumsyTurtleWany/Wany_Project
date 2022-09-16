#include "BackgroundMap.hpp"
#include "UserState_Idle.hpp"

BackgroundMap::BackgroundMap()// : currentState(new UserState_Idle(this))
{
	pObj = new object2D<float>;
	pObj->type = OBJECT_TYPE::STATIC_OBJECT;
	pObj->createShader(ShaderType::Texture);
}

BackgroundMap::BackgroundMap(const Rect2f& _rect)// : currentState(new UserState_Idle(this))
{
	pObj = new object2D<float>(_rect);
	pObj->type = OBJECT_TYPE::STATIC_OBJECT;
	pObj->createShader(ShaderType::Texture);
}

BackgroundMap::~BackgroundMap()
{
	release();
}

bool BackgroundMap::initialize()
{
	return true;
}

bool BackgroundMap::frame(float _dt)
{
	if (!pObj->frame(_dt))
	{
		return false;
	}

	return true;
}

bool BackgroundMap::render()
{
	if (!pObj->render())
	{
		return false;
	}

	return true;
}

bool BackgroundMap::release()
{
	pObj->release();
	delete pObj;
	pObj = nullptr;
	return true; // currentState->release();
}