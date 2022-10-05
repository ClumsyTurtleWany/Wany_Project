#include "UserInterface.hpp"
#include "DXTextureManager.hpp"
#include "UI_Button.hpp"

UserInterface::UserInterface()
{
}

UserInterface::UserInterface(UserInterface* _src)
{
	copy(_src);
}

UserInterface::UserInterface(const Rect2f& _rect)
{
}

UserInterface::~UserInterface()
{
}

bool UserInterface::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();
		size_t extensionIdx = filename.find_last_of(L".");
		std::wstring key = filename.substr(0, extensionIdx);

		if (fileExtension == L"")
		{
			if (filename == L"font")
			{
				LoadFont(filepath);
			}
			else if (filename == L"btn")
			{
				LoadBtn(filepath);
			}
		}
		else if (fileExtension == L".txt")
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
				textureKeyMap.insert(std::make_pair(key, filepath));
			}
		}
	}

	return true;
}

bool UserInterface::LoadInfo(std::wstring _path)
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
			UserInterface::Info data;
			
			std::string lineData;
			std::getline(file, lineData, '=');
			std::wstring key(lineData.begin(), lineData.end());
			data.textureKey = key;

			std::getline(file, lineData, ',');
			data.pos.x = std::stof(lineData);

			std::getline(file, lineData, '\n');
			data.pos.y = std::stof(lineData);
			
			infoList.push_back(data);
		}
		file.close();
		return true;
	}
}

bool UserInterface::LoadFont(std::wstring _path, std::map<std::wstring, std::wstring>* _dst)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();
		size_t extensionIdx = filename.find_last_of(L".");
		std::wstring key = filename.substr(0, extensionIdx);

		if (fileExtension == L"")
		{
			std::map<std::wstring, std::wstring> fontMap;
			if (LoadFont(filepath, &fontMap))
			{
				fontMapList.insert(std::make_pair(key, fontMap));
			}		
		}
		else
		{
			if (DXTextureManager::getInstance()->Load(filepath))
			{
				if (_dst != nullptr)
				{
					_dst->insert(std::make_pair(key, filepath));
				}
				else
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool UserInterface::LoadBtn(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();
		size_t extensionIdx = filename.find_last_of(L".");
		std::wstring key = filename.substr(0, extensionIdx);

		if (fileExtension == L"")
		{
			UI_Button* newBtn = new UI_Button;
			if (newBtn->Load(filepath))
			{
				newBtn->initialize();
				newBtn->setPos(pos);
				childList.push_back(newBtn);
			}
			else
			{
				delete newBtn;
				newBtn = nullptr;
			}
		}
		else
		{
			continue;
		}
	}

	return true;
}

void UserInterface::setPos(Vector2f _pos)
{
	pos = _pos;
}

void UserInterface::setPlayer(Player* _user)
{
	user = _user;
}

void UserInterface::addChild(UserInterface* _child)
{
	childList.push_back(_child);
}

void UserInterface::copy(UserInterface* _src)
{
	textureKeyMap.insert(_src->textureKeyMap.begin(), _src->textureKeyMap.end());
	infoList.assign(_src->infoList.begin(), _src->infoList.end());
	fontMapList.insert(_src->fontMapList.begin(), _src->fontMapList.end());
	childList.assign(_src->childList.begin(), _src->childList.end());
}

bool UserInterface::initialize()
{
	this->createShader(ShaderType::Texture);
	return true;
}

bool UserInterface::frame()
{
	for (auto it : childList)
	{
		it->frame();
	}

	return true;
}

bool UserInterface::render()
{
	for (auto it : infoList)
	{
		auto iter = textureKeyMap.find(it.textureKey);
		if (iter != textureKeyMap.end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iter->second);
			if (pTexture != nullptr)
			{
				float width = pTexture->getWidth();
				float height = pTexture->getHeight();
				Rect2f drawRect(pos.x + it.pos.x, pos.y + it.pos.y, width, height);
				this->shape = drawRect;
				setTexture(pTexture);

				object2D<float>::render();
			}
		}
	}

	for (auto it : childList)
	{
		it->render();
	}

	return true;
}

bool UserInterface::release()
{
	return false;
}
