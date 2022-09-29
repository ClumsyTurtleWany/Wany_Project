#include "SkillManager.hpp"
#include "DXTextureManager.hpp"

void SkillManager::setUser(Player* _user)
{
	user = _user;
}

bool SkillManager::Load(std::wstring _path)
{
	// recursive_directory_iterator ��� �� ���� �������� ��� Ž��.
	/*std::filesystem::path path(_path);
	for (auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();
		Load(filepath);
	}*/

	// directory_iterator ��� �� ���� ������ Ž��. ���� ���� Ž�� �� ��������� ���� ȣ�� �ʿ�.
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();
		
		if (file.path().extension() == L"")
		{
			std::wstring dir = filepath + L"/";
			auto it = skillList.find(dir);
			if (it != skillList.end())
			{
				continue;
			}

			Skill* newSkill = new Skill;
			newSkill->skillName = filename;
			newSkill->user = user;
			if (newSkill->Load(dir))
			{
				newSkill->initialize();
				skillList.insert(std::make_pair(filename, newSkill));
			}
		}
		else
		{
			continue;
		}
	}

	return true;
}

Skill* SkillManager::getSkill(std::wstring _name)
{
	auto it = skillList.find(_name);
	if (it != skillList.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

bool SkillManager::addSkillToJobList(std::wstring _name)
{
	Skill* targetSkill = getSkill(_name);
	if (targetSkill == nullptr)
	{
		return false;
	}

	bool isExist = false;
	Skill* jobSkill = nullptr;
	for (auto it : jobList)
	{
		if (it->skillName == targetSkill->skillName)
		{
			isExist = true;
			jobSkill = it;
		}
	}

	if (isExist)
	{
		if (jobSkill->isEnd && jobSkill->isCoolDown())
		{
			Skill* pSkill = new Skill(targetSkill);
			pSkill->initialize();
			jobList.push_back(pSkill);
		}
	}
	else
	{
		Skill* pSkill = new Skill(targetSkill);
		pSkill->initialize();
		jobList.push_back(pSkill);
	}

	/*Skill* targetSkill = getSkill(_name);
	if (targetSkill != nullptr)
	{
		bool isExist = false;
		for (auto it : jobList)
		{
			if (it == targetSkill)
			{
				isExist = true;
			}
		}

		if (!isExist)
		{
			Skill* pSkill = new Skill(targetSkill);
			pSkill->initialize();
			pSkill->totalTime = 0.0f;
			jobList.push_back(pSkill);
		}
		else
		{
			if (targetSkill->isCoolDown() && targetSkill->isEnd)
			{
				Skill* pSkill = new Skill(targetSkill);
				pSkill->initialize();
				pSkill->totalTime = 0.0f;
				jobList.push_back(pSkill);
			}
		}
	}*/
	return true;
}

bool SkillManager::initialize()
{
	return true;
}

bool SkillManager::frame()
{
	for (auto it = jobList.begin(); it != jobList.end(); )
	{
		if ((*it)->isEnd && (*it)->isCoolDown())
		{
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

bool SkillManager::render()
{
	for (auto it : jobList)
	{
		it->render();
	}

	return true;
}

bool SkillManager::release()
{
	jobList.clear();

	for (auto it : skillList)
	{
		Skill* pSkill = it.second;
		delete pSkill;
		pSkill = nullptr;
	}
	skillList.clear();
	return true;
}
