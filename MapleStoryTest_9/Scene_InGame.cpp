#include "Scene_InGame.hpp"
#include "DXWriter.hpp"
#include "EffectManager.hpp"
#include "NPCManager.hpp"
#include "DXTextureManager.hpp"
#include "SkillManager.hpp"
#include "Input.hpp"
//#include "UI_HPStatus.hpp"
//#include "UI_Exit.hpp"
//#include "UI_Exp.hpp"
//#include "UI_Button.hpp"
#include "MapManager.hpp"


void GameExit()
{
	PostQuitMessage(0);
}

Scene_InGame::Scene_InGame(MapleStory* _game) : Scene(_game)
{
	initialize();
}

bool Scene_InGame::changeCurrentMap(std::wstring _name, Vector2f _pos)
{
	if (currentMap != nullptr)
	{
		currentMap->StopBGM();
	}

	currentMap = MapManager::getInstance()->getMap(_name);
	if (currentMap == nullptr)
	{
		return false;
	}
	
	//user->currentMap = currentMap;
	//user->mapWidth = currentMap->mapWidth;
	//user->mapHeight = currentMap->mapHeight;
	//renderCamera->setPos(user->getCenter());
	//user->setCamera(renderCamera);

	currentMap->setUser(user);
	currentMap->PlayBGM();
	renderCamera->setBoundary(currentMap->shape);

	user->currentMap = currentMap;
	user->mapWidth = currentMap->mapWidth;
	user->mapHeight = currentMap->mapHeight;
	renderCamera->setPos(user->getCenter());
	user->moveTo(_pos);
	user->setCamera(renderCamera);	

	return true;
}

bool Scene_InGame::initialize()
{
	if (renderCamera == nullptr) 
	{
		RECT clientRect = g_pWindow->getClientRect();
		renderCamera = new Camera;
		renderCamera->setPos(Vector2f(0, 0));
		renderCamera->setWidth(clientRect.right - clientRect.left);
		renderCamera->setHeight(clientRect.bottom - clientRect.top);
		DXShaderBorderManager::getInstance()->setCamera(renderCamera);
	}

	EffectManager::getInstance()->setCamera(renderCamera);
	NPCManager::getInstance()->setCamera(renderCamera);

	MapManager::getInstance()->setScene(this);
	MapManager::getInstance()->setCamera(renderCamera);
	MapManager::getInstance()->Load(MAP_DIRECTORY);

	//currentMap = MapManager::getInstance()->getMap(L"Happy");
	//currentMap->PlayBGM();
	//renderCamera->setBoundary(currentMap->shape);

	if (DXTextureManager::getInstance()->Load(USER_CHARACTER_0))
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(USER_CHARACTER_0);
		float width = pTexture->getWidth();
		float height = pTexture->getHeight();
		//float x = (currentMap->mapWidth - width) * 0.5f;
		//float y = (currentMap->mapHeight - height) * 0.5f;
		
		//user = new Player(Rect2f(x, y, width, height));
		user = new Player(Rect2f(0, 0, width, height));
		user->initialize();
		user->createShader(ShaderType::Texture);
		user->setTexture(pTexture);
	}

	changeCurrentMap(user->info.currentMapName, user->info.currentMapPos);

	//user->currentMap = currentMap;
	//user->mapWidth = currentMap->mapWidth;
	//user->mapHeight = currentMap->mapHeight;
	//renderCamera->setPos(user->getCenter());
	//user->setCamera(renderCamera);

	SkillManager::getInstance()->setUser(user);
	SkillManager::getInstance()->Load(SKILL_DIRECTORY);
	EffectManager::getInstance()->Load(EFFECT_DIRECTORY);
	NPCManager::getInstance()->Load(NPC_DIRECTORY);
	UIManager::getInstance()->Load(UI_DIRECTORY);

	// HP Status
	HPStatus = new UI_HPStatus;
	HPStatus->initialize();
	//HPStatus->setPos(Vector2f(584.0f, 690.0f));
	HPStatus->setPos(Vector2f(561.0f, 680.0f)); // aspectRatio == 1.2
	HPStatus->setPlayer(user);
	uiList.push_back(HPStatus);

	// Exp Bar
	UI_Exp* uiExp = new UI_Exp;
	uiExp->initialize();
	uiExp->setPos(Vector2f(0.0f, 760.0f));
	uiExp->setPlayer(user);
	uiList.push_back(uiExp);

	// Exit Dialog
	uiExit = new UI_Exit;
	uiExit->setPos(Vector2f(450.0f, 250.0f));
	uiExit->setPlayer(user);
	uiExit->initialize();

	return true;
}

bool Scene_InGame::frame()
{
	float dt = Timer::getInstance()->getDeltaTime();

	if (currentMap != nullptr)
	{
		currentMap->frame(dt);
	}

	if (user != nullptr)
	{
		user->frame(dt);
		renderCamera->setPos(user->getCenter());
		renderCamera->frame();
	}

	SkillManager::getInstance()->frame();
	EffectManager::getInstance()->frame();

	KeyState keyState_ESC = Input::getInstance()->getKey(VK_ESCAPE);
	if ((keyState_ESC == KeyState::Down) || (keyState_ESC == KeyState::Hold))
	{
		bool isExist = false;
		for (auto it : uiList)
		{
			if (it == uiExit)
			{
				isExist = true;
			}
		}

		if (!isExist)
		{
			uiList.push_back(uiExit);
		}
	}

	for (auto it = uiList.begin(); it != uiList.end(); )
	{
		if ((*it)->isClose)
		{
			(*it)->isClose = false;
			it = uiList.erase(it);
		}
		else
		{
			(*it)->frame();
		}

		if (it != uiList.end())
		{
			it++;
		}
	}

	return true;
}

bool Scene_InGame::render()
{
	if (currentMap != nullptr)
	{
		currentMap->render();
	}

	if (user != nullptr)
	{
		user->render();
	}

	SkillManager::getInstance()->render();
	EffectManager::getInstance()->render();

	/*std::wstring wstrMapSize;
	wstrMapSize += L"Map Size: ";
	wstrMapSize += std::to_wstring(static_cast<int>(currentMap->shape.width()));
	wstrMapSize += L", ";
	wstrMapSize += std::to_wstring(static_cast<int>(currentMap->shape.height()));
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
	DXWriter::getInstance()->draw(0, 75, wstrCameraPos);*/

	for (auto it : uiList)
	{
		it->render();
	}

	return true;
}

bool Scene_InGame::release()
{
	if (uiExit != nullptr)
	{
		delete uiExit;
		uiExit = nullptr;
	}

	if (uiExp != nullptr)
	{
		delete uiExp;
		uiExp = nullptr;
	}

	if (HPStatus != nullptr)
	{
		delete HPStatus;
		HPStatus = nullptr;
	}
	uiList.clear();

	if (user != nullptr)
	{
		delete user;
		user = nullptr;
	}

	if (renderCamera != nullptr)
	{
		delete renderCamera;
		renderCamera = nullptr;
	}

	return true;
}