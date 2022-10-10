#include "Map.hpp"
#include "UserState_Idle.hpp"
#include "Player.hpp"
#include "Timer.hpp"
#include "NPCManager.hpp"
#include "Portal.hpp"

Map::Map()
{
	createShader(ShaderType::Texture);
}

Map::Map(const Rect2f& _rect)
{
	this->shape = _rect;
	createShader(ShaderType::Texture);
	if (collisionMap == nullptr)
	{
		collisionMap = new QuadTree<float>;
		collisionMap->create(&this->shape);
	}
}

Map::~Map()
{
	release();
}

bool Map::CreateMonster(int _npcIdx, int _spawnIdx)
{
	SpawnPoint spawnPoint = spawnPointList[_spawnIdx];
	NPC* pMonster = NPCManager::getInstance()->CreateNPC(monsterNameList[_npcIdx]);

	float spawn_x = spawnPoint.pos.x;
	float spawn_y = spawnPoint.pos.y - pMonster->shape.height();
	pMonster->moveTo(spawn_x, spawn_y);
	pMonster->setColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	pMonster->mapWidth = mapWidth;
	pMonster->mapHeight = mapHeight;
	pMonster->boundaryRect = spawnPoint.boundary;

	npcList.push_back(pMonster);
	collisionMap->addObject(pMonster);

	return true;
}

bool Map::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();
		size_t extensionIdx = filename.find_last_of(L".");
		std::wstring key = filename.substr(0, extensionIdx);

		if (file.path().extension() == L".txt")
		{
			if (filename == L"info.txt")
			{
				LoadInfo(filepath);
			}
		}
		else
		{
			if (DXTextureManager::getInstance()->Load(filepath))
			{
				mapTextureList.insert(std::make_pair(key, filepath));
			}
		}
	}

	return true;
}

bool Map::LoadInfo(std::wstring _path)
{
	std::fstream file(_path);
	if (!file.is_open())
	{
		return false;
	}
	else
	{
		while (!file.eof())
		{
			std::string dataName;
			std::getline(file, dataName, '=');
			if (dataName == "bgm")
			{
				std::string lineData;
				std::getline(file, lineData, '\n');
				std::wstring bgmName(lineData.begin(), lineData.end());

				BGM = FMODSoundManager::getInstance()->getSound(bgmName);
				BGM->setLoop(true);
			}
			else if (dataName == "monster")
			{
				std::string lineData;
				std::getline(file, lineData, '\n');
				int monsterCnt = std::stoi(lineData);
				for (int i = 0; i < monsterCnt; i++)
				{
					std::getline(file, lineData, '\n');
					std::wstring monsterName(lineData.begin(), lineData.end());
					monsterNameList.push_back(monsterName);
				}
			}
			else if (dataName == "npc")
			{
				std::string lineData;
				std::getline(file, lineData, '\n');
				int npcCnt = std::stoi(lineData);
				for (int i = 0; i < npcCnt; i++)
				{
					std::getline(file, lineData, '\n');
					std::wstring npcName(lineData.begin(), lineData.end());
					npcNameList.push_back(npcName);
				}
			}
			else if (dataName == "floor")
			{
				std::string lineData;
				std::getline(file, lineData, '\n');
				int floorCnt = std::stoi(lineData);
				for (int i = 0; i < floorCnt; i++)
				{
					std::getline(file, lineData, ',');
					float x = std::stof(lineData);

					std::getline(file, lineData, ',');
					float y = std::stof(lineData);

					std::getline(file, lineData, ',');
					float width = std::stof(lineData);

					std::getline(file, lineData, ',');
					float height = std::stof(lineData);

					MapObject* newMapObject = new MapObject(Rect2f(x, y, width, height), MapObjectType::Floor);
					
					std::getline(file, lineData, ',');
					int spawnCnt = std::stoi(lineData);
					float offset_x = width / static_cast<float>(spawnCnt + 1);
					for (int cnt = 0; cnt < spawnCnt; cnt++)
					{
						SpawnPoint spawnPoint;
						spawnPoint.pos.x = x + offset_x * (cnt + 1);
						spawnPoint.pos.y = y;
						spawnPoint.boundary = Rect2f(x, 0, width, y);
						spawnPointList.push_back(spawnPoint);
					}

					std::getline(file, lineData, '\n');
					int pierce = std::stoi(lineData);
					if (pierce == 1)
					{
						newMapObject->isPierce = true;
					}
					else if (pierce == 0)
					{
						newMapObject->isPierce = false;
					}

					mapObjectList.push_back(newMapObject);
				}
			}
			else if (dataName == "rope")
			{
				std::string lineData;
				std::getline(file, lineData, '\n');
				int ropeCnt = std::stoi(lineData);
				for (int i = 0; i < ropeCnt; i++)
				{
					std::getline(file, lineData, ',');
					float x = std::stof(lineData);

					std::getline(file, lineData, ',');
					float y = std::stof(lineData);

					std::getline(file, lineData, ',');
					float width = std::stof(lineData);

					std::getline(file, lineData, '\n');
					float height = std::stof(lineData);

					MapObject* newMapObject = new MapObject(Rect2f(x, y, width, height), MapObjectType::Rope);
					mapObjectList.push_back(newMapObject);
				}
			}
			else if (dataName == "portal")
			{
				std::string lineData;
				std::getline(file, lineData, '\n');
				int portalCnt = std::stoi(lineData);
				for (int i = 0; i < portalCnt; i++)
				{
					std::getline(file, lineData, ',');
					float x = std::stof(lineData);

					std::getline(file, lineData, ',');
					float y = std::stof(lineData);

					std::getline(file, lineData, ',');
					float width = std::stof(lineData);

					std::getline(file, lineData, '\n');
					float height = std::stof(lineData);

					Portal* newPortal = new Portal(Rect2f(x, y, width, height));

					std::getline(file, lineData, '\n');
					std::wstring dstMap(lineData.begin(), lineData.end());
					newPortal->setDstMap(dstMap);

					Vector2f dstPos;
					std::getline(file, lineData, ',');
					dstPos.x = std::stof(lineData);
					std::getline(file, lineData, '\n');
					dstPos.y = std::stof(lineData);
					newPortal->setDstPos(dstPos);

					portalList.push_back(newPortal);
				}
			}
		}
		file.close();
		return true;
	}
}

void Map::setUser(Player* _user)
{
	user = _user;
}

void Map::setSceneToPortal(Scene_InGame* _InGame)
{
	for (auto it : portalList)
	{
		it->setScene(_InGame);
	}
}

void Map::PlayBGM()
{
	BGM->play();
}

void Map::StopBGM()
{
	BGM->stop();
}

void Map::setMapName(std::wstring _name)
{
	mapName = _name;
}

std::wstring Map::getMapName()
{
	return mapName;
}

bool Map::Collision(object2D<float>* _src, std::vector<object2D<float>*>* _dst, std::vector<Rect_<float>>* _dstSection)
{
	return collisionMap->Collision(_src, _dst, _dstSection);
}

bool Map::CollisionMapObject(object2D<float>* _obj, MapObjectType _targetType, std::vector<object2D<float>*>* _dst, std::vector<Rect_<float>>* _dstSection)
{
	bool isCollision = false;
	for (auto it : mapObjectList)
	{
		if ((it->mapObjectType == _targetType))
		{
			Rect2f intersection;
			if (_obj->shape.intersectRect(it->shape, &intersection))
			{
				if (_dst != nullptr)
				{
					_dst->push_back(it);
				}

				if (_dstSection != nullptr)
				{
					_dstSection->push_back(intersection);
				}

				DrawBorder(it->shape, BORDER_COLOR_RED);
				isCollision = true;
			}
		}
		else
		{
			continue;
		}
	}
	return isCollision;
}

bool Map::CollisionPortal(object2D<float>* _obj, std::vector<Portal*>* _dst)
{
	bool isCollision = false;
	for (auto it : portalList)
	{
		if (it->hitbox.RectInRect(_obj->hitbox))
		{
			isCollision = true;
			_dst->push_back(it);
		}
	}
	return isCollision;
}

void Map::updateShader()
{
	std::vector<Vertex>* list = pShader->getVertexList();
	list->at(0).pos = { -1.0f, 1.0f, 0.0f };
	list->at(1).pos = { 1.0f, 1.0f, 0.0f };
	list->at(2).pos = { -1.0f, -1.0f, 0.0f };
	list->at(3).pos = { 1.0f, -1.0f, 0.0f };

	list->at(0).color = { 1.0f, 1.0f, 1.0f, 1.0f };
	list->at(1).color = { 1.0f, 1.0f, 1.0f, 1.0f };
	list->at(2).color = { 1.0f, 1.0f, 1.0f, 1.0f };
	list->at(3).color = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (renderCamera != nullptr)
	{
		Rect2f rectCamera = renderCamera->getRect();
		Rect2f rectTexture;
		rectTexture.LT.x = rectCamera.LT.x / mapWidth;
		rectTexture.LT.y = rectCamera.LT.y / mapHeight;
		rectTexture.RB.x = rectCamera.RB.x / mapWidth;
		rectTexture.RB.y = rectCamera.RB.y / mapHeight;

		list->at(0).texture = { rectTexture.LT.x, rectTexture.LT.y }; // p1-LT
		list->at(1).texture = { rectTexture.RB.x, rectTexture.LT.y }; // p2-RT
		list->at(2).texture = { rectTexture.LT.x, rectTexture.RB.y }; // p3-LB
		list->at(3).texture = { rectTexture.RB.x, rectTexture.RB.y }; // p4-RB
	}
}

void Map::updateShaderCamera()
{
	std::vector<Vertex>* list = pShader->getVertexList();
	list->at(0).pos = { -1.0f, 1.0f, 0.0f };
	list->at(1).pos = { 1.0f, 1.0f, 0.0f };
	list->at(2).pos = { -1.0f, -1.0f, 0.0f };
	list->at(3).pos = { 1.0f, -1.0f, 0.0f };

	list->at(0).color = { 1.0f, 1.0f, 1.0f, 1.0f };
	list->at(1).color = { 1.0f, 1.0f, 1.0f, 1.0f };
	list->at(2).color = { 1.0f, 1.0f, 1.0f, 1.0f };
	list->at(3).color = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (renderCamera != nullptr)
	{
		Rect2f rectCamera = renderCamera->getRect();
		Rect2f rectTexture;
		rectTexture.LT.x = rectCamera.LT.x / mapWidth;
		rectTexture.LT.y = rectCamera.LT.y / mapHeight;
		rectTexture.RB.x = rectCamera.RB.x / mapWidth;
		rectTexture.RB.y = rectCamera.RB.y / mapHeight;

		list->at(0).texture = { rectTexture.LT.x, rectTexture.LT.y }; // p1-LT
		list->at(1).texture = { rectTexture.RB.x, rectTexture.LT.y }; // p2-RT
		list->at(2).texture = { rectTexture.LT.x, rectTexture.RB.y }; // p3-LB
		list->at(3).texture = { rectTexture.RB.x, rectTexture.RB.y }; // p4-RB
	}

}

bool Map::initialize()
{
	object2D<float>::initialize();

	auto it = mapTextureList.find(L"map");
	if (it != mapTextureList.end())
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(it->second);
		mapWidth = pTexture->getWidth();
		mapHeight = pTexture->getHeight();
		shape = Rect2f(0, 0, mapWidth, mapHeight);
		setTexture(pTexture);
	}

	if (collisionMap == nullptr)
	{
		collisionMap = new QuadTree<float>;
		collisionMap->create(&this->shape);
	}

	for (auto it : mapObjectList)
	{
		it->setCamera(renderCamera);
		it->mapWidth = mapWidth;
		it->mapHeight = mapHeight;
		it->initialize();
	}

	for (auto it : portalList)
	{
		it->setCamera(renderCamera);
		it->mapWidth = mapWidth;
		it->mapHeight = mapHeight;
		it->initialize();
	}

	size_t monsterTypeCnt = monsterNameList.size();
	maxMonster = spawnPointList.size();
	for (size_t idx = 0; idx < maxMonster; idx++)
	{
		int monsterType = rand() % monsterTypeCnt;

		CreateMonster(monsterType, idx);
	}

	beforeTime = Timer::getInstance()->getPlayTime();
	timeCounter = 0.0f;
	spawnTime = 15.0f;

	return true;
}

bool Map::frame(float _dt)
{
	float currentTime = Timer::getInstance()->getPlayTime();
	float secondPerFrame = currentTime - beforeTime;
	timeCounter += secondPerFrame;
	beforeTime = currentTime;

	if (!object2D<float>::frame(_dt))
	{
		return false;
	}

	for (auto it : mapObjectList)
	{
		it->frame(_dt);
	}

	for (auto it : portalList)
	{
		it->frame(_dt);
	}

	for (auto it = npcList.begin(); it != npcList.end();)
	{
		if ((*it)->deleteFlag)
		{
			delete* it;
			*it = nullptr;
			it = npcList.erase(it);
			continue;
		}
		else
		{
			(*it)->frame(_dt);

			if (!user->invincible)
			{
				if ((*it)->hitbox.intersectRect(user->hitbox))
				{
					user->hit((*it)->info.minDamage);
				}
			}
		}
		it++;
	}

	if (timeCounter >= spawnTime)
	{
		timeCounter = 0.0f;
		int cnt = maxMonster - npcList.size();
		for (int i = 0; i < cnt; i++)
		{
			int randMonster = rand() % monsterNameList.size();
			int randSpawnPoint = rand() % spawnPointList.size();
			CreateMonster(randMonster, randSpawnPoint);
		}
	}

	collisionMap->updateDynamicObject();

	return true;
}

bool Map::render()
{
	if (!object2D<float>::render())
	{
		return false;
	}

	for (auto it : npcList)
	{
		it->render();
	}

	collisionMap->render();

	for (auto it : mapObjectList)
	{
		it->render();
		DrawBorder(it->shape, BORDER_COLOR_YELLOW);
	}

	for (auto it : portalList)
	{
		it->render();
		DrawBorder(it->shape, BORDER_COLOR_YELLOW);
	}

	return true;
}

bool Map::release()
{
	if (collisionMap != nullptr)
	{
		delete collisionMap;
		collisionMap = nullptr;
	}

	object2D<float>::release();
	return true; // currentState->release();
}