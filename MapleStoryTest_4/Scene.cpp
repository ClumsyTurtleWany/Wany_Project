#include "Scene.hpp"
#include "DXWriter.hpp"

void Scene::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool Scene::initialize()
{
	RECT clientRect = g_pWindow->getClientRect();
	renderCamera = new Camera;
	renderCamera->setPos(Vector2f(0, 0));
	renderCamera->setWidth(clientRect.right - clientRect.left);
	renderCamera->setHeight(clientRect.bottom - clientRect.top);
	DXShaderBorderManager::getInstance()->setCamera(renderCamera);
	EffectManager::getInstance()->setCamera(renderCamera);
	NPCManager::getInstance()->setCamera(renderCamera);

	beforeTime = 0.0f;

	return true;
}

bool Scene::frame()
{
	float dt = Timer::getInstance()->getDeltaTime();

	if (background != nullptr)
	{
		background->frame(dt);
	}
	
	if (user != nullptr)
	{
		user->frame(dt);
		renderCamera->setPos(user->getCenter());
		renderCamera->frame();
	}


	/*float currentTime = Timer::getInstance()->getPlayTime();
	float secondPerFrame = currentTime - beforeTime;
	timeCounter += secondPerFrame;
	if (timeCounter >= 0.5f)
	{
		timeCounter = 0.0f;
		float x = 100 + rand() % 1000;
		float y = 100 + rand() % 1000;

		EffectManager::getInstance()->addEffectToJobList(Vector2f(x, y), L"Skill_0");
		
	}
	beforeTime = currentTime;*/


	SkillManager::getInstance()->frame();
	EffectManager::getInstance()->frame();

	/*for (auto it : MonsterList)
	{
		it->frame(dt);
	}*/

	/*for (auto it : NPCList)
	{
		it->frame(dt);
	}*/

	for (auto it = NPCList.begin(); it != NPCList.end();)
	{
		if ((*it)->deleteFlag)
		{
			delete *it;
			*it = nullptr;
			it = NPCList.erase(it);
			continue;
		}
		else
		{
			(*it)->frame(dt);
		}
		it++;
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

	for (auto it : NPCList)
	{
		it->render();
	}

	if (user != nullptr)
	{
		user->render();
	}

	SkillManager::getInstance()->render();
	EffectManager::getInstance()->render();
	
	std::wstring wstrMapSize;
	wstrMapSize += L"Map Size: ";
	wstrMapSize += std::to_wstring(static_cast<int>(background->shape.width()));
	wstrMapSize += L", ";
	wstrMapSize += std::to_wstring(static_cast<int>(background->shape.height()));
	DXWriter::getInstance()->draw(0, 25, wstrMapSize);

	std::wstring wstrUserPos;
	wstrUserPos += L"User Position: ";
	wstrUserPos += std::to_wstring(static_cast<int>(user->shape.LT.x));
	wstrUserPos += L", ";
	wstrUserPos += std::to_wstring(static_cast<int>(user->shape.LT.y));
	DXWriter::getInstance()->draw(0, 50, wstrUserPos);

	std::wstring wstrCameraPos;
	wstrCameraPos += L"Camera LT: ";
	wstrCameraPos += std::to_wstring(static_cast<int>(renderCamera->getRect().LT.x));
	wstrCameraPos += L", ";
	wstrCameraPos += std::to_wstring(static_cast<int>(renderCamera->getRect().LT.y));
	wstrCameraPos += L", RB: ";
	wstrCameraPos += std::to_wstring(static_cast<int>(renderCamera->getRect().RB.x));
	wstrCameraPos += L", ";
	wstrCameraPos += std::to_wstring(static_cast<int>(renderCamera->getRect().RB.y));
	wstrCameraPos += L", Center: ";
	wstrCameraPos += std::to_wstring(static_cast<int>((renderCamera->getRect().LT.x + renderCamera->getRect().RB.x) / 2));
	wstrCameraPos += L", ";
	wstrCameraPos += std::to_wstring(static_cast<int>((renderCamera->getRect().LT.y + renderCamera->getRect().RB.y) / 2));
	DXWriter::getInstance()->draw(0, 75, wstrCameraPos);

	

	//background->CollisionMapObject(user);

	return true;
}

bool Scene::release()
{
	if (renderCamera != nullptr)
	{
		delete renderCamera;
		renderCamera = nullptr;
	}
	return true;
}
