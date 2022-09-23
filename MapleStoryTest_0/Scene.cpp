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
	return true;
}

bool Scene::frame()
{
	if (user != nullptr)
	{
		user->frame(Timer::getInstance()->getDeltaTime());
		renderCamera->setPos(user->getCenter());
		renderCamera->frame();
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

	for (auto it : MonsterList)
	{
		it->render();
	}

	/*for (auto it : NPCList)
	{
		it->render();
	}*/

	collisionMap->render();
	return true;
}

bool Scene::release()
{
	if (collisionMap != nullptr)
	{
		delete collisionMap;
		collisionMap = nullptr;
	}

	if (renderCamera != nullptr)
	{
		delete renderCamera;
		renderCamera = nullptr;
	}
	return true;
}
