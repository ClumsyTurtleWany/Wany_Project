#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "Map.hpp"
#include "Camera.hpp"
#include <fstream>

class UserState;

struct PlayerInfo
{
	enum class Job
	{
		Warrior,
		Archer,
		Thief,
		Magician,
		Pirate,
		Beginner,
	};

	Job job = PlayerInfo::Job::Beginner;
	int strength = 4;
	int dexterity = 4;
	int lucky = 4;
	int intelligence = 4;
	int maxHP = 50;
	int maxMP = 50;
	int currentHP = 50;
	int currentMP = 50;
	int exp = 0;
	int level = 1;
	int minDamage = 1;
	int maxDamage = 1;

	float getAttackPoint()
	{
		if (job == Job::Warrior)
		{
			return strength * 2.0f * maxDamage;
		}
		else if (job == Job::Archer)
		{
			return dexterity * 2.0f * maxDamage;
		}
		else if (job == Job::Thief)
		{
			return lucky * 2.0f * maxDamage;
		}
		else if (job == Job::Magician)
		{
			return intelligence * 2.0f * maxDamage;
		}
		else if (job == Job::Pirate)
		{
			return strength * 1.0f * maxDamage + dexterity * 1.0f * maxDamage;
		}
		else
		{
			return strength * 1.0f * maxDamage;
		}
	}

	bool load(std::wstring _path)
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
				if (dataName == "job")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					if (lineData == "Warrior")
					{
						job = PlayerInfo::Job::Warrior;
					}
					else if (lineData == "Archer")
					{
						job = PlayerInfo::Job::Archer;
					}
					else if (lineData == "Thief")
					{
						job = PlayerInfo::Job::Thief;
					}
					else if (lineData == "Magician")
					{
						job = PlayerInfo::Job::Magician;
					}
					else if (lineData == "Pirate")
					{
						job = PlayerInfo::Job::Pirate;
					}
					else
					{
						job = PlayerInfo::Job::Beginner;
					}
				}
				else if (dataName == "strength")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					strength = std::stoi(lineData);
				}
				else if (dataName == "dexterity")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					dexterity = std::stoi(lineData);
				}
				else if (dataName == "lucky")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					lucky = std::stoi(lineData);
				}
				else if (dataName == "intelligence")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					intelligence = std::stoi(lineData);
				}
				else if (dataName == "maxHP")
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
				else if (dataName == "currentHP")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					currentHP = std::stoi(lineData);
				}
				else if (dataName == "currentMP")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					currentMP = std::stoi(lineData);
				}
				else if (dataName == "exp")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					exp = std::stoi(lineData);
				}
				else if (dataName == "level")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					level = std::stoi(lineData);
				}
			}
			file.close();
			return true;
		}

		return false;
	}
};

class Player : public object2D<float>
{
protected:
	UserState* currentState;

public:
	//object2D<float>* pObj;
	
	PlayerInfo info;

	enum class Direction
	{
		Left,
		Right
	};

	Direction currentDirection = Direction::Left;

	Map* currentMap = nullptr;

public:
	Player();
	Player(const Rect2f& _rect);
	virtual ~Player();

public:
	virtual bool initialize();
	virtual bool frame(float _dt);
	virtual bool render();
	virtual bool release();

public:
	void setCamera(Camera* _camera);

public:
	Rect2f getRect();
	Vector2f getCenter();

public:
	template <typename T>
	void changeCurrentState();
};

template <typename T>
void Player::changeCurrentState()
{
	delete currentState;
	currentState = nullptr;
	currentState = new T(this);
}