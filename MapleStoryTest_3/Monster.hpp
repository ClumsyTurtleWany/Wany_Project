#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"
#include <fstream>

class MonsterState;

struct MonsterInfo
{
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
			}
			file.close();
			return true;
		}

		return false;
	}
};

class Monster : public object2D<float>
{
protected:
	MonsterState* currentState;

public:
	enum class Direction
	{
		Left,
		Right
	};

	MonsterInfo info;
	Direction currentDirection;
	SpaceDivision* currentMap;

	std::vector<std::wstring> textureKeyList;
	std::map<std::wstring, std::vector<Rect2f>> spriteList;

public:
	Monster();
	Monster(Monster* _src);
	Monster(const Rect2f& _rect);
	virtual ~Monster();

public:
	void hit(float _hitPoint);
	bool Load(std::wstring _path);
	bool LoadInfo(std::wstring _path);
	bool LoadSprite(std::wstring _path);

public:
	virtual bool initialize();
	virtual bool frame(float _dt);
	virtual bool render();
	virtual bool release();

//public:
//	template <typename T>
//	void changeCurrentState();
};

//template <typename T>
//void Monster::changeCurrentState()
//{
//	delete currentState;
//	currentState = nullptr;
//	currentState = new T(this);
//}