#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"
#include <fstream>

class NPCState;

struct NPCInfo
{
	enum class RenderType
	{
		Texture,
		Sprite
	};

	enum class NPCType
	{
		Monster,
		NPC
	};

	NPCType type = NPCType::Monster;
	RenderType renderType = RenderType::Sprite;
	int maxHP = 50;
	int maxMP = 0;
	int currentHP = 50;
	int currentMP = 0;
	int exp = 100;
	float defaultAttackDamage = 1.0f;
	int minDamage = 1;
	int maxDamage = 1;

	bool Load(std::wstring _path)
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
				
				if (dataName == "maxHP")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					maxHP = std::stoi(lineData);
				}
				else if (dataName == "maxMP")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					maxMP = std::stoi(lineData);
				}
				else if (dataName == "exp")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					exp = std::stoi(lineData);
				}
				else if (dataName == "minDamage")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					minDamage = std::stoi(lineData);
				}
				else if (dataName == "maxDamage")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					maxDamage = std::stoi(lineData);
				}
				else if (dataName == "type")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					if (lineData == "Sprite")
					{
						RenderType renderType = RenderType::Sprite;
					}
					else if (lineData == "Texture")
					{
						RenderType renderType = RenderType::Texture;
					}
				}
			}
			file.close();
			return true;
		}

		return false;
	}
};

class NPC : public object2D<float>
{
protected:
	NPCState* currentState;

public:
	enum class Direction
	{
		Left,
		Right
	};

	std::wstring NPCName = L"";
	NPCInfo info;
	Direction currentDirection = Direction::Left;
	SpaceDivision* currentMap;
	Vector2f pos;
	Rect2f boundaryRect;
	bool deleteFlag = false;

public:
	NPC();
	NPC(const Rect2f& _rect);
	virtual ~NPC();

public:
	void hit(float _hitPoint);
	//bool Load(std::wstring _path);
	//bool LoadInfo(std::wstring _path);
	//bool LoadSprite(std::wstring _path);

public:
	virtual bool initialize();
	virtual bool frame(float _dt);
	virtual bool render();
	virtual bool release();

public:
	template <typename T>
	void changeCurrentState();
};

template <typename T>
void NPC::changeCurrentState()
{
	delete currentState;
	currentState = nullptr;
	currentState = new T(this);
}