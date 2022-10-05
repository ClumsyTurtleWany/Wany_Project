#include "MapManager.hpp"

bool MapManager::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();

		if (file.path().extension() == L"")
		{
			std::wstring dir = filepath + L"/";
			auto it = mapList.find(filename);
			if (it != mapList.end())
			{
				continue;
			}

			std::unique_ptr<Map> newMap = std::make_unique<Map>();
			if (newMap->Load(dir))
			{
				newMap->setMapName(filename);
				newMap->setCamera(renderCamera);
				newMap->initialize();
				mapList.insert(std::make_pair(filename, std::move(newMap)));
			}
		}
		else
		{
			continue;
		}
	}

	return true;
}

void MapManager::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

Map* MapManager::getMap(std::wstring _name)
{
	auto it = mapList.find(_name);
	if (it != mapList.end())
	{
		return it->second.get();
	}
	else
	{
		return nullptr;
	}
}

bool MapManager::initialize()
{
	return true;
}

bool MapManager::frame()
{
	return true;
}

bool MapManager::render()
{
	return true;
}

bool MapManager::release()
{
	mapList.clear();
	return true;
}
