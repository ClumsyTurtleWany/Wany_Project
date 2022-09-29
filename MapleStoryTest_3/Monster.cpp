#include "Monster.hpp"
#include "DXTextureManager.hpp"

Monster::Monster()// : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>;
	type = OBJECT_TYPE::DYNAMIC_OBJECT;
	createShader(ShaderType::Normal);
}

Monster::Monster(Monster* _src)
{
}

Monster::Monster(const Rect2f& _rect)// : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>(_rect);
	type = OBJECT_TYPE::DYNAMIC_OBJECT;
	createShader(ShaderType::Normal);
}

Monster::~Monster()
{
	release();
}

void Monster::hit(float _hitPoint)
{
	info.currentHP -= _hitPoint;

}

bool Monster::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();

		if (fileExtension == L"")
		{
			return false;
		}
		else if (fileExtension == L".txt")
		{
			if (filename == L"info.txt")
			{
				LoadInfo(filepath);
			}
			else if (filename == L"sprite.txt")
			{
				LoadSprite(filepath);
			}
		}
		else
		{
			if (DXTextureManager::getInstance()->Load(filepath))
			{
				textureKeyList.push_back(filepath);
			}
		}
	}

	return true;
}

bool Monster::LoadInfo(std::wstring _path)
{
	return info.Load(_path);
}

bool Monster::LoadSprite(std::wstring _path)
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
			std::wstring key(dataName.begin(), dataName.end());
			if (key == L"")
			{
				break;
			}

			std::string lineData;
			std::getline(file, lineData, '\n');
			int cnt = std::stoi(lineData);
			std::vector<Rect2f> rectList;
			for (int i = 0; i < cnt; i++)
			{
				std::string lineData;
				std::getline(file, lineData, ',');
				int number = std::stoi(lineData);

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

			spriteList.insert(std::make_pair(key, rectList));
		}
		file.close();
		return true;
	}
}

bool Monster::initialize()
{
	return true;
}

bool Monster::frame(float _dt)
{
	if (!object2D<float>::frame(_dt))
	{
		return false;
	}

	/*if (!currentState->frame())
	{
		return false;
	}*/

	hitbox = shape;

	return true;
}

bool Monster::render()
{
	if (!object2D<float>::render())
	{
		return false;
	}

	DrawBorder(hitbox, BORDER_COLOR_BLUE);

	/*if (!currentState->render())
	{
		return false;
	}*/

	return true;
}

bool Monster::release()
{
	return true; // currentState->release();
}