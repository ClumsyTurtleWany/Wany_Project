#include "Scene_InGame.hpp"
#include "UI_HPStatus.hpp"
#include "UI_Exp.hpp"
#include "UI_Button.hpp"
#include "DXWriter.hpp"

void GameExit()
{
	PostQuitMessage(0);
}

Scene_InGame::Scene_InGame(MapleStory* _game) : Scene(_game)
{
	initialize();
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

	// Create Background Map.
	if (DXTextureManager::getInstance()->Load(MAP_SCENE_0))
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(MAP_SCENE_0);
		float width = pTexture->getWidth();
		float height = pTexture->getHeight();
		Rect2f rect(0, 0, width, height);
		currentMap = new Map(rect);
		currentMap->createShader(ShaderType::Texture);
		currentMap->setTexture(pTexture);
		//collisionMap = new QuadTree<float>;
		//collisionMap->create(&rect);
		renderCamera->setBoundary(rect);

		currentMap->mapWidth = width;
		currentMap->mapHeight = height;

		currentMap->renderCamera = renderCamera;
		DXShaderBorderManager::getInstance()->setMapSize(Vector2f(width, height));

		// 중앙 상단 발판 545, 455, 1048, 20 - 로프1 618, 455, 10, 222,  로프2  1499, 455, 10, 222
		MapObject* Stepbox_0 = new MapObject(Rect2f(545, 455, 1048, 20), MapObjectType::Floor);
		MapObject* Stepbox_0_rope_0 = new MapObject(Rect2f(618, 455, 10, 222), MapObjectType::Rope);
		MapObject* Stepbox_0_rope_1 = new MapObject(Rect2f(1499, 455, 10, 222), MapObjectType::Rope);
		currentMap->addMapObject(Stepbox_0);
		currentMap->addMapObject(Stepbox_0_rope_0);
		currentMap->addMapObject(Stepbox_0_rope_1);

		// 왼쪽 상단 발판 0, 723, 836, 20 - 로프 64, 723, 10, 257
		MapObject* Stepbox_1 = new MapObject(Rect2f(0, 723, 836, 20), MapObjectType::Floor);
		MapObject* Stepbox_1_rope_0 = new MapObject(Rect2f(64, 723, 10, 257), MapObjectType::Rope);
		currentMap->addMapObject(Stepbox_1);
		currentMap->addMapObject(Stepbox_1_rope_0);

		// 왼쪽 하단 발판 0, 1024, 750, 20 - 로프 604, 1024, 10, 185
		MapObject* Stepbox_2 = new MapObject(Rect2f(0, 1024, 750, 20), MapObjectType::Floor);
		MapObject* Stepbox_2_rope_0 = new MapObject(Rect2f(604, 1024, 10, 185), MapObjectType::Rope);
		currentMap->addMapObject(Stepbox_2);
		currentMap->addMapObject(Stepbox_2_rope_0);

		// 오른쪽 상단 발판 1255, 723, 840, 20 - 로프 2016, 723, 10, 257
		MapObject* Stepbox_3 = new MapObject(Rect2f(1255, 723, 840, 20), MapObjectType::Floor);
		MapObject* Stepbox_3_rope_0 = new MapObject(Rect2f(2016, 723, 10, 257), MapObjectType::Rope);
		currentMap->addMapObject(Stepbox_3);
		currentMap->addMapObject(Stepbox_3_rope_0);

		// 오른쪽 하단 발판 1345, 1024, 750, 20 - 로프 1485, 1024, 10, 185
		MapObject* Stepbox_4 = new MapObject(Rect2f(1345, 1024, 750, 20), MapObjectType::Floor);
		MapObject* Stepbox_4_rope_0 = new MapObject(Rect2f(1485, 1024, 10, 185), MapObjectType::Rope);
		currentMap->addMapObject(Stepbox_4);
		currentMap->addMapObject(Stepbox_4_rope_0);

		// 바닥 0, 1255, 2095, 155
		MapObject* floor = new MapObject(Rect2f(0, 1255, 2095, 155), MapObjectType::Floor);
		floor->isPierce = false;
		currentMap->addMapObject(floor);

		if (FMODSoundManager::getInstance()->LoadDir(SOUND_DIRECTORY))
		{
			FMODSound* pSound = FMODSoundManager::getInstance()->getSound(L"BadGuys.mp3");
			currentMap->setBGM(pSound);
		}
		currentMap->initialize();
	}

	if (DXTextureManager::getInstance()->Load(USER_CHARACTER_0))
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(USER_CHARACTER_0);
		float width = pTexture->getWidth();
		float height = pTexture->getHeight();
		float x = (currentMap->mapWidth - width) * 0.5f;
		float y = (currentMap->mapHeight - height) * 0.5f;
		
		user = new Player(Rect2f(x, y, width, height));
		user->initialize();
		user->createShader(ShaderType::Texture);
		user->setTexture(pTexture);
	}

	user->currentMap = currentMap;
	user->mapWidth = currentMap->mapWidth;
	user->mapHeight = currentMap->mapHeight;
	renderCamera->setPos(user->getCenter());
	user->setCamera(renderCamera);

	SkillManager::getInstance()->setUser(user);
	SkillManager::getInstance()->Load(SKILL_DIRECTORY);
	EffectManager::getInstance()->Load(EFFECT_DIRECTORY);
	NPCManager::getInstance()->Load(NPC_DIRECTORY);
	UIManager::getInstance()->Load(UI_DIRECTORY);

	NPCInfo info = NPCManager::getInstance()->getNPCInfo(L"Happy_Erda");

	std::map<std::wstring, std::vector<std::wstring>> testMap;
	NPCManager::getInstance()->getTextureKeyMap(L"Happy_Erda", testMap);

	std::map<std::wstring, std::vector<Rect2f>> testSpriteList;
	NPCManager::getInstance()->getSpriteMap(L"Happy_Erda", testSpriteList);

	/*for (int i = 0; i < 10; i++)
	{
		NPC* pMonster = NPCManager::getInstance()->CreateNPC(L"Happy_Erda");
		pMonster->Random();
		pMonster->setColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
		pMonster->mapWidth = currentMap->mapWidth;
		pMonster->mapHeight = currentMap->mapHeight;
		pMonster->boundaryRect = Rect2f(0, 0, currentMap->mapWidth, currentMap->mapHeight);

		NPCList.push_back(pMonster);
		currentMap->addObject(pMonster);
	}*/

	for (auto it : currentMap->mapObjectList)
	{
		if (it->type == MapObjectType::Floor)
		{
			/*if (it->isPierce)
			{
				continue;
			}*/

			float x = it->shape.LT.x;
			float y = 0;
			float width = it->shape.width();
			float height = it->shape.LT.y;
			Rect2f boundaryRect(x, y, width, height);
			for (int i = 0; i < 5; i++)
			{
				NPC* pMonster = NPCManager::getInstance()->CreateNPC(L"Happy_Erda");
				float spawn_x = x + (rand() % static_cast<int>(width));
				float spawn_y = height - pMonster->shape.height();
				pMonster->moveTo(spawn_x, spawn_y);
				pMonster->setColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
				pMonster->mapWidth = currentMap->mapWidth;
				pMonster->mapHeight = currentMap->mapHeight;
				pMonster->boundaryRect = boundaryRect;

				NPCList.push_back(pMonster);
				currentMap->addObject(pMonster);
			}
		}
	}


	//UserInterface* HP_bar = UIManager::getInstance()->CreateUI(Vector2f(584.0f, 690.0f), L"HP_bar");
	//uiList.push_back(HP_bar);

	//UserInterface* Exp_bar = UIManager::getInstance()->CreateUI(Vector2f(0.0f, 760.0f), L"Exp_bar");
	//uiList.push_back(Exp_bar);

	UI_HPStatus* HPStatus = new UI_HPStatus;
	HPStatus->initialize();
	//HPStatus->setPos(Vector2f(584.0f, 690.0f));
	HPStatus->setPos(Vector2f(561.0f, 680.0f)); // aspectRatio == 1.2
	HPStatus->setPlayer(user);
	uiList.push_back(HPStatus);

	UI_Exp* uiExp = new UI_Exp;
	uiExp->initialize();
	uiExp->setPos(Vector2f(0.0f, 760.0f));
	uiExp->setPlayer(user);
	uiList.push_back(uiExp);

	UI_Button* uiBtn = new UI_Button;
	if (uiBtn->Load(L"../resource/MapleStory/UI/Exit/btn/yes/"))
	{
		uiBtn->initialize();
		uiBtn->setPos(Vector2f(0.0f, 0.0f));
		uiBtn->setCallbackFunction(GameExit);
		uiList.push_back(uiBtn);
	}

	return true;
}

bool Scene_InGame::frame()
{
	float dt = Timer::getInstance()->getDeltaTime();

	for (auto it = NPCList.begin(); it != NPCList.end();)
	{
		if ((*it)->deleteFlag)
		{
			delete* it;
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

	for (auto it : uiList)
	{
		it->frame();
	}

	return true;
}

bool Scene_InGame::render()
{
	if (currentMap != nullptr)
	{
		currentMap->render();
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
	DXWriter::getInstance()->draw(0, 75, wstrCameraPos);


	for (auto it : uiList)
	{
		it->render();
	}

	return true;
}

bool Scene_InGame::release()
{
	if (renderCamera != nullptr)
	{
		delete renderCamera;
		renderCamera = nullptr;
	}

	return true;
}

//bool Scene_InGame::frame()
//{
//	user->frame(Timer::getInstance()->getDeltaTime());
//
//	for (auto it : enemyList)
//	{
//		it->frame();
//	}
//
//	for (auto it : NPCList)
//	{
//		it->frame();
//	}
//
//	return false;
//}
//
//bool Scene_InGame::render()
//{
//	return false;
//}
//
//bool Scene_InGame::release()
//{
//	return false;
//}
