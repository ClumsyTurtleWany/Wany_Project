#include "NPC.hpp"
#include "DXTextureManager.hpp"
#include "NPCState_Idle.hpp"

NPC::NPC() //: currentState(new NPCState_Idle(this))
{
	//pObj = new object2D<float>;
	type = OBJECT_TYPE::DYNAMIC_OBJECT;
	//createShader(ShaderType::Normal);
}

NPC::NPC(const Rect2f& _rect) //: currentState(new NPCState_Idle(this))
{
	//pObj = new object2D<float>(_rect);
	type = OBJECT_TYPE::DYNAMIC_OBJECT;
	shape = _rect;
	//createShader(ShaderType::Normal);
}

NPC::~NPC()
{
	release();
}

void NPC::hit(float _hitPoint)
{
	info.currentHP -= _hitPoint;

}

//bool NPC::Load(std::wstring _path)
//{
//	std::filesystem::path path(_path);
//	for (auto& file : std::filesystem::directory_iterator(path))
//	{
//		std::wstring filepath = file.path();
//		std::wstring filename = file.path().filename();
//		std::wstring fileExtension = file.path().extension();
//
//		if (fileExtension == L"")
//		{
//			return false;
//		}
//		else if (fileExtension == L".txt")
//		{
//			if (filename == L"info.txt")
//			{
//				LoadInfo(filepath);
//			}
//			else if (filename == L"sprite.txt")
//			{
//				LoadSprite(filepath);
//			}
//		}
//		else
//		{
//			if (DXTextureManager::getInstance()->Load(filepath))
//			{
//				textureKeyList.push_back(filepath);
//			}
//		}
//	}
//
//	return true;
//}
//
//bool NPC::LoadInfo(std::wstring _path)
//{
//	return info.Load(_path);
//}
//
//bool NPC::LoadSprite(std::wstring _path)
//{
//	std::fstream file(_path);
//	if (!file.is_open())
//	{
//		return false;
//	}
//	else
//	{
//		while (!file.eof())
//		{
//			std::string dataName;
//			std::getline(file, dataName, '=');
//			std::wstring key(dataName.begin(), dataName.end());
//			if (key == L"")
//			{
//				break;
//			}
//
//			std::string lineData;
//			std::getline(file, lineData, '\n');
//			int cnt = std::stoi(lineData);
//			std::vector<Rect2f> rectList;
//			for (int i = 0; i < cnt; i++)
//			{
//				std::string lineData;
//				std::getline(file, lineData, ',');
//				int number = std::stoi(lineData);
//
//				std::getline(file, lineData, ',');
//				int x = std::stof(lineData);
//				std::getline(file, lineData, ',');
//				int y = std::stof(lineData);
//				std::getline(file, lineData, ',');
//				int width = std::stof(lineData);
//				std::getline(file, lineData, '\n');
//				int height = std::stof(lineData);
//
//				rectList.push_back(Rect2f(x, y, width, height));
//			}
//
//			spriteList.insert(std::make_pair(key, rectList));
//		}
//		file.close();
//		return true;
//	}
//}

bool NPC::initialize()
{
	currentState = new NPCState_Idle(this);
	return true;
}

bool NPC::frame(float _dt)
{
	object2D<float>::frame(_dt);
	/*if (!pObj->frame(_dt))
	{
		return false;
	}*/

	if (!currentState->frame())
	{
		return false;
	}

	//accel = force / mass;
	//velocity += accel * _dt;
	//velocity = accel * _dt;
	//Vector2f distance = velocity * _dt;
	//shape.offset(distance);

	Vector2f distance = force * _dt;
	shape.offset(distance);

	if (shape.LT.x < boundaryRect.LT.x)
	{
		moveTo(boundaryRect.LT.x, shape.LT.y);
		//Rect2f rectTemp = shape;
		//float width = rectTemp.width();
		//shape.LT.x = boundaryRect.LT.x;
		//shape.RB.x = shape.LT.x + width - 1;
	}

	if (shape.LT.y < boundaryRect.LT.y)
	{
		moveTo(shape.LT.x, boundaryRect.LT.y);
		//Rect2f rectTemp = shape;
		//shape.LT.y = boundaryRect.LT.y;
		//shape.RB.y = shape.LT.y + rectTemp.height() - 1;
	}

	if (shape.RB.x > boundaryRect.RB.x)
	{
		moveTo(shape.RB.x - shape.width(), shape.LT.y);
		//Rect2f rectTemp = shape;
		//shape.RB.x = boundaryRect.RB.x;
		//shape.LT.x = shape.RB.x - rectTemp.width() + 1;
	}

	if (shape.RB.y > boundaryRect.RB.y)
	{
		moveTo(shape.LT.x, shape.RB.y - shape.height());
		//Rect2f rectTemp = shape;
		//shape.RB.y = boundaryRect.RB.y;
		//shape.LT.y = shape.RB.y - rectTemp.height() + 1;
	}

	hitbox = shape;

	return true;
}

bool NPC::render()
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

bool NPC::release()
{
	return true; // currentState->release();
}