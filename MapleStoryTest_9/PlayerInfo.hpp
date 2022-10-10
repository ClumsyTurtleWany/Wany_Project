#pragma once

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
	std::wstring name;
	int strength = 4;
	int dexterity = 4;
	int lucky = 4;
	int intelligence = 4;
	int maxHP = 50;
	int maxMP = 50;
	int currentHP = 50;
	int currentMP = 50;
	int currentExp = 0;
	int requiredExp = 200;
	int level = 1;
	int minDamage = 1;
	int maxDamage = 5;
	std::wstring currentMapName = L"Happy";
	Vector2f currentMapPos = Vector2f(0, 0);

	float getAttackPoint()
	{
		int diff = (maxDamage - minDamage) > 0 ? (maxDamage - minDamage) : 1;
		int randDamage = rand() % diff;
		return (minDamage + randDamage);

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
				else if (dataName == "currentExp")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					currentExp = std::stoi(lineData);
				}
				else if (dataName == "requiredExp")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					requiredExp = std::stoi(lineData);
				}
				else if (dataName == "level")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					level = std::stoi(lineData);
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
				else if (dataName == "currentMap")
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
					currentMapName.assign(lineData.begin(), lineData.end());
				}
				else if (dataName == "currentMapPos")
				{
					std::string lineData;
					std::getline(file, lineData, ',');
					currentMapPos.x = std::stof(lineData);
					std::getline(file, lineData, '\n');
					currentMapPos.y = std::stof(lineData);
				}
				else
				{
					std::string lineData;
					std::getline(file, lineData, '\n');
				}
			}
			file.close();
			return true;
		}

		return false;
	}
	bool Save(std::wstring _path)
	{
		std::fstream file(_path, std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
		if (!file.is_open())
		{
			return false;
		}
		else
		{
			Job job = PlayerInfo::Job::Beginner;
			if (job == PlayerInfo::Job::Warrior)
			{
				file << "job=Warrior" << std::endl;
			}
			else if (job == PlayerInfo::Job::Archer)
			{
				file << "job=Archer" << std::endl;
			}
			else if (job == PlayerInfo::Job::Thief)
			{
				file << "job=Thief" << std::endl;
			}
			else if (job == PlayerInfo::Job::Magician)
			{
				file << "job=Magician" << std::endl;
			}
			else if (job == PlayerInfo::Job::Pirate)
			{
				file << "job=Pirate" << std::endl;
			}
			else
			{
				file << "job=Beginner" << std::endl;
			}
			
			file << "strength=" << strength << std::endl;
			file << "dexterity=" << dexterity << std::endl;
			file << "lucky=" << lucky << std::endl;
			file << "intelligence=" << intelligence << std::endl;
			file << "maxHP=" << maxHP << std::endl;
			file << "maxMP=" << maxMP << std::endl;
			file << "currentHP=" << currentHP << std::endl;
			file << "currentMP=" << currentMP << std::endl;
			file << "currentExp=" << currentExp << std::endl;
			file << "requiredExp=" << requiredExp << std::endl;
			file << "level=" << level << std::endl;
			file << "minDamage=" << minDamage << std::endl;
			file << "maxDamage=" << maxDamage << std::endl;

			std::string strCurrentMapName(currentMapName.begin(), currentMapName.end());
			file << "currentMap=" << strCurrentMapName << std::endl;
			file << "currentMapPos=" << currentMapPos.x << ", " << currentMapPos.y << std::endl;
			file.close();
			return true;
		}
	}

};
