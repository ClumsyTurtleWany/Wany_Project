#include "Scene.hpp"

void Scene::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool Scene::initialize()
{
	return true;
}

bool Scene::frame()
{
	user->frame(Timer::getInstance()->getDeltaTime());

	for (auto it : MonsterList)
	{
		it->frame(Timer::getInstance()->getDeltaTime());
	}

	for (auto it : NPCList)
	{
		it->frame();
	}

	return true;
}

bool Scene::render()
{
	user->render();

	for (auto it : MonsterList)
	{
		it->render();
	}

	for (auto it : NPCList)
	{
		it->render();
	}

	worldMap->render();
	return true;
}

bool Scene::release()
{
	if (worldMap != nullptr)
	{
		delete worldMap;
		worldMap = nullptr;
	}
	return true;
}
