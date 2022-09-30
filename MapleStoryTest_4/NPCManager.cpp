#include "NPCManager.hpp"

bool NPCManager::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();

		if (fileExtension == L"")
		{
			auto it = infoList.find(filename);
			if (it != infoList.end())
			{
				continue;
			}
			else
			{
				LoadNPC(filepath, filename);
			}
		}
		else
		{
			continue;
		}
	}

	return true;
}

bool NPCManager::LoadNPC(std::wstring _path, std::wstring _key)
{
	std::filesystem::path path(_path);
	std::map<std::wstring, std::vector<std::wstring>> textureMapList;
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();

		if (fileExtension == L"")
		{
			auto it = textureKeyMapList.find(_key);
			if (it != textureKeyMapList.end())
			{
				continue;
			}
			else
			{
				std::vector<std::wstring> textureList;
				if (LoadTexture(filepath, textureList))
				{
					textureMapList.insert(std::make_pair(filename, textureList));
				}
			}
		}
		else if (fileExtension == L".txt")
		{
			if (filename == L"info.txt")
			{
				LoadInfo(filepath, _key);
			}
			else if (filename == L"sprite.txt")
			{
				LoadSprite(filepath, _key);
			}
		}
		else
		{
			if (DXTextureManager::getInstance()->Load(filepath))
			{
				std::vector<std::wstring> defaultList;
				std::map<std::wstring, std::vector<std::wstring>> defaultMap;
				defaultList.push_back(filepath);
				defaultMap.insert(std::make_pair(L"Sprite", defaultList));

				auto it = textureKeyMapList.find(_key);
				if (it == textureKeyMapList.end())
				{
					textureKeyMapList.insert(std::make_pair(_key, defaultMap));
				}
			}
			continue;
		}
	}

	textureKeyMapList.insert(std::make_pair(_key, textureMapList));

	return true;
}

bool NPCManager::LoadTexture(std::wstring _path, std::vector<std::wstring>& _list)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();

		if (DXTextureManager::getInstance()->Load(filepath))
		{
			_list.push_back(filepath);
		}
	}

	return true;
}

bool NPCManager::LoadInfo(std::wstring _path, std::wstring _key)
{
	NPCInfo info;
	if (info.Load(_path))
	{
		infoList.insert(std::make_pair(_key, info));
		return true;
	}
	else
	{
		return false;
	}	
}

bool NPCManager::LoadSprite(std::wstring _path, std::wstring _key)
{
	std::fstream file(_path);
	if (!file.is_open())
	{
		return false;
	}
	else
	{
		std::map<std::wstring, std::vector<Rect2f>> stateList;
		std::map<std::wstring, Vector2f> stateOffsetList;
		while (!file.eof())
		{
			// State Name
			std::string dataName;
			std::getline(file, dataName, '=');
			std::wstring key(dataName.begin(), dataName.end());
			if (key == L"")
			{
				break;
			}

			// State Amount
			std::string lineData;
			std::getline(file, lineData, '\n');
			int cnt = std::stoi(lineData);

			// Offset_x
			std::getline(file, lineData, '=');
			std::getline(file, lineData, '\n');
			float offset_x = std::stof(lineData);

			// Offset_y
			std::getline(file, lineData, '=');
			std::getline(file, lineData, '\n');
			float offset_y = std::stof(lineData);

			// Sprite Rect
			std::vector<Rect2f> rectList;
			for (int i = 0; i < cnt; i++)
			{
				// State Number
				std::getline(file, lineData, ',');
				int number = std::stoi(lineData);

				// Rect x, y, width, height
				std::getline(file, lineData, ',');
				int x = std::stof(lineData);
				std::getline(file, lineData, ',');
				int y = std::stof(lineData);
				std::getline(file, lineData, ',');
				int width = std::stof(lineData);
				std::getline(file, lineData, '\n');
				int height = std::stof(lineData);

				rectList.push_back(Rect2f(x, y, width, height));
			}

			stateOffsetList.insert(std::make_pair(key, Vector2f(offset_x, offset_y)));
			stateList.insert(std::make_pair(key, rectList));
		}
		file.close();

		spriteMapList.insert(std::make_pair(_key, stateList));
		spriteOffsetMapList.insert(std::make_pair(_key, stateOffsetList));
		return true;
	}
}

void NPCManager::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

NPCInfo NPCManager::getNPCInfo(std::wstring _name)
{
	auto it = infoList.find(_name);
	if (it != infoList.end())
	{
		return it->second;
	}
	else
	{
		return NPCInfo();
	}
}

bool NPCManager::getTextureKeyMap(std::wstring _name, std::map<std::wstring, std::vector<std::wstring>>& _map)
{
	auto it = textureKeyMapList.find(_name);
	if (it != textureKeyMapList.end())
	{
		_map.insert(it->second.begin(), it->second.end());
		return true;
	}
	else
	{
		return false;
	}
}

bool NPCManager::getSpriteMap(std::wstring _name, std::map<std::wstring, std::vector<Rect2f>>& _map)
{
	auto it = spriteMapList.find(_name);
	if (it != spriteMapList.end())
	{
		_map.insert(it->second.begin(), it->second.end());
		return true;
	}
	else
	{
		return false;
	}
}

bool NPCManager::getSpriteOffsetMap(std::wstring _name, std::map<std::wstring, Vector2f>& _map)
{
	auto it = spriteOffsetMapList.find(_name);
	if (it != spriteOffsetMapList.end())
	{
		_map.insert(it->second.begin(), it->second.end());
		return true;
	}
	else
	{
		return false;
	}
}

NPC* NPCManager::CreateNPC(std::wstring _name)
{
	NPC* newNPC = new NPC;
	newNPC->NPCName = _name;
	newNPC->info = getNPCInfo(_name);
	newNPC->createShader(ShaderType::Texture);
	newNPC->setCamera(renderCamera);
	newNPC->initialize();
	NPCList.push_back(newNPC);

	return newNPC;
}

//bool NPCManager::addMonsterToJobList(Vector2f _pos, std::wstring _name)
//{
//	//auto it = npcList.find(_name);
//	//if (it != npcList.end())
//	//{
//	//	NPC* pEffect = new NPC(it->second.get());
//	//	//pEffect = it->second.get();
//	//	pEffect->initialize();
//	//	pEffect->setCamera(renderCamera);
//	//	pEffect->setPos(_pos);
//	//	//pEffect->moveCenterTo(_pos);
//	//	jobList.push_back(pEffect);
//	//	return true;
//	//}
//	//else
//	//{
//	//	return false;
//	//}
//	return true;
//}

bool NPCManager::initialize()
{
	return true;
}

bool NPCManager::frame()
{
	/*for (auto it = jobList.begin(); it != jobList.end(); )
	{
		if ((*it)->isEnd)
		{
			NPC* pEffect = *it;
			delete pEffect;
			pEffect = nullptr;
			it = jobList.erase(it);
		}
		else
		{
			(*it)->frame();
		}

		if (it != jobList.end())
		{
			it++;
		}
	}*/

	return true;
}

bool NPCManager::render()
{
	//for (auto it : jobList)
	//{
	//	/*if (it->isEnd)
	//	{
	//		NPC* pEffect = it;
	//		delete pEffect;
	//		pEffect = nullptr;
	//	}
	//	else
	//	{
	//		it->render();
	//	}*/
	//	it->render();
	//}

	return true;
}

bool NPCManager::release()
{
	for (auto it : NPCList)
	{
		NPC* pNPC = it;
		delete pNPC;
		pNPC = nullptr;
	}
	NPCList.clear();

	infoList.clear();
	textureKeyMapList.clear();
	spriteMapList.clear();
	return true;
}
