#include "MonsterManager.hpp"

bool MonsterManager::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();

		if (file.path().extension() == L"")
		{
			std::wstring dir = filepath + L"/";
			auto it = monsterList.find(dir);
			if (it != monsterList.end())
			{
				continue;
			}

			std::unique_ptr<Monster> newMonster = std::make_unique<Monster>();
			if (newMonster->Load(dir))
			{
				newMonster->initialize();
				monsterList.insert(std::make_pair(filename, std::move(newMonster)));
			}
		}
		else
		{
			continue;
		}
	}

	return true;
}

void MonsterManager::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

Monster* MonsterManager::getMonster(std::wstring _name)
{
	auto it = monsterList.find(_name);
	if (it != monsterList.end())
	{
		return it->second.get();
	}
	else
	{
		return nullptr;
	}
}

bool MonsterManager::addMonsterToJobList(Vector2f _pos, std::wstring _name)
{
	//auto it = monsterList.find(_name);
	//if (it != monsterList.end())
	//{
	//	Monster* pEffect = new Monster(it->second.get());
	//	//pEffect = it->second.get();
	//	pEffect->initialize();
	//	pEffect->setCamera(renderCamera);
	//	pEffect->setPos(_pos);
	//	//pEffect->moveCenterTo(_pos);
	//	jobList.push_back(pEffect);
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	return true;
}

bool MonsterManager::initialize()
{
	return true;
}

bool MonsterManager::frame()
{
	/*for (auto it = jobList.begin(); it != jobList.end(); )
	{
		if ((*it)->isEnd)
		{
			Monster* pEffect = *it;
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

bool MonsterManager::render()
{
	//for (auto it : jobList)
	//{
	//	/*if (it->isEnd)
	//	{
	//		Monster* pEffect = it;
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

bool MonsterManager::release()
{
	for (auto it : jobList)
	{
		Monster* pEffect = it;
		delete pEffect;
		pEffect = nullptr;
	}

	monsterList.clear();
	return true;
}
