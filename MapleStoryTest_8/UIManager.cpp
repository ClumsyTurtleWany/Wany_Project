#include "UIManager.hpp"

bool UIManager::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();

		if (file.path().extension() == L"")
		{
			std::wstring dir = filepath + L"/";
			auto it = uiList.find(filename);
			if (it != uiList.end())
			{
				continue;
			}

			std::unique_ptr<UserInterface> newUI = std::make_unique<UserInterface>();
			if (newUI->Load(dir))
			{
				newUI->initialize();
				uiList.insert(std::make_pair(filename, std::move(newUI)));
			}
		}
		else
		{
			continue;
		}
	}

	return true;
}

UserInterface* UIManager::CreateUI(Vector2f _pos, std::wstring _name)
{
	auto it = uiList.find(_name);
	if (it != uiList.end())
	{
		UserInterface* pUserInterface = new UserInterface(it->second.get());
		pUserInterface->initialize();
		pUserInterface->setPos(_pos);
		jobList.push_back(pUserInterface);
		return pUserInterface;
	}
	else
	{
		return nullptr;
	}
}

UserInterface* UIManager::getUI(std::wstring _name)
{
	auto it = uiList.find(_name);
	if (it != uiList.end())
	{
		return it->second.get();
	}
	else
	{
		return nullptr;
	}
}

bool UIManager::initialize()
{
	return false;
}

bool UIManager::frame()
{
	return false;
}

bool UIManager::render()
{
	return false;
}

bool UIManager::release()
{
	return false;
}
