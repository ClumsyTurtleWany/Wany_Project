#include "Scene.hpp"

void Scene::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool Scene::initialize()
{
	RECT clientRect = g_pWindow->getClientRect();
	renderCamera.setPos(Vector2f(0, 0));
	renderCamera.setWidth(clientRect.right - clientRect.left);
	renderCamera.setHeight(clientRect.bottom - clientRect.top);
	return true;
}

bool Scene::frame()
{
	if (user != nullptr)
	{
		user->frame(Timer::getInstance()->getDeltaTime());
		renderCamera.setPos(user->getCenter());
		renderCamera.frame();
	}

	for (auto it : MonsterList)
	{
		it->frame(Timer::getInstance()->getDeltaTime());
	}

	for (auto it : NPCList)
	{
		it->frame();
	}

	//collisionMap->updateDynamicObject();
	return true;
}

bool Scene::render()
{
	if (background != nullptr)
	{
		background->render();
	}

	if (user != nullptr)
	{
		user->render();
	}

	/*for (auto it : MonsterList)
	{
		it->render();
	}

	for (auto it : NPCList)
	{
		it->render();
	}

	collisionMap->render();*/
	return true;
}

bool Scene::release()
{
	if (collisionMap != nullptr)
	{
		delete collisionMap;
		collisionMap = nullptr;
	}
	return true;
}
