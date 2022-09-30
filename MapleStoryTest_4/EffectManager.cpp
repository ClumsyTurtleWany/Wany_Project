#include "EffectManager.hpp"

bool EffectManager::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();

		if (file.path().extension() == L"")
		{
			std::wstring dir = filepath + L"/";
			auto it = effectList.find(dir);
			if (it != effectList.end())
			{
				continue;
			}

			std::unique_ptr<Effect> newEffect = std::make_unique<Effect>();
			if (newEffect->Load(dir))
			{
				newEffect->initialize();
				effectList.insert(std::make_pair(filename, std::move(newEffect)));
			}
		}
		else
		{
			continue;
		}
	}

	return true;
}

void EffectManager::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

bool EffectManager::addEffectToJobList(Vector2f _pos, std::wstring _name)
{
	auto it = effectList.find(_name);
	if (it != effectList.end())
	{
		Effect* pEffect = new Effect(it->second.get());
		//pEffect = it->second.get();
		pEffect->initialize();
		pEffect->setCamera(renderCamera);
		pEffect->setPos(_pos);
		//pEffect->moveCenterTo(_pos);
		jobList.push_back(pEffect);
		return true;
	}
	else
	{
		return false;
	}
}

bool EffectManager::initialize()
{
	return true;
}

bool EffectManager::frame()
{
	for (auto it = jobList.begin(); it != jobList.end(); )
	{
		if ((*it)->isEnd)
		{
			Effect* pEffect = *it;
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
	}

	return true;
}

bool EffectManager::render()
{
	for (auto it : jobList)
	{
		/*if (it->isEnd)
		{
			Effect* pEffect = it;
			delete pEffect;
			pEffect = nullptr;
		}
		else
		{
			it->render();
		}*/
		it->render();
	}

	return true;
}

bool EffectManager::release()
{
	for (auto it : jobList)
	{
		Effect* pEffect = it;
		delete pEffect;
		pEffect = nullptr;
	}

	effectList.clear();
	return true;
}
