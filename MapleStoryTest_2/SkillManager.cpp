#include "SkillManager.hpp"
#include "DXTextureManager.hpp"

void SkillManager::setUser(Player* _user)
{
	user = _user;
}

bool SkillManager::LoadDir(std::wstring _path)
{
	// recursive_directory_iterator 사용 시 하위 폴더까지 모두 탐색.
	/*std::filesystem::path path(_path);
	for (auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();
		Load(filepath);
	}*/

	// directory_iterator 사용 시 현재 폴더만 탐색. 하위 폴더 탐색 시 재귀적으로 폴더 호출 필요.
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();
		
		if (file.path().extension() == L"")
		{
			Skill* newSkill = new Skill;
			std::wstring dir = filepath + L"/";

			auto it = skillList.find(dir);
			if (it != skillList.end())
			{
				continue;
			}

			if (LoadSkill(dir, newSkill))
			{
				skillNameList.push_back(filename);
				newSkill->user = user;
				newSkill->initialize();
				skillList.insert(std::make_pair(filename, newSkill));
			}
			else
			{
				delete newSkill;
				newSkill = nullptr;
			}
		}
		else
		{
			continue;
		}
	}

	return true;
}

//bool SkillManager::LoadDir_New(std::wstring _path)
//{
//	// 2022-09-26 Test
//
//	std::filesystem::path path(_path);
//	for (auto& file : std::filesystem::directory_iterator(path))
//	{
//		std::vector<Skill*> newSkillList;
//
//		std::wstring filename = file.path().filename();
//		std::wstring filepath = file.path();
//
//		if (file.path().extension() == L"")
//		{
//			//Skill* newSkill = new Skill;
//			std::wstring dir = filepath + L"/";
//
//			auto it = skillList.find(dir);
//			if (it != skillList.end())
//			{
//				continue;
//			}
//
//			if (LoadSkill_New(dir, &newSkillList))
//			{
//				skillNameList.push_back(dir);
//				skillVectorList.insert(std::make_pair(dir, newSkillList));
//			}
//			else
//			{
//				//delete newSkill;
//				//newSkill = nullptr;
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//
//	return true;
//}

bool SkillManager::LoadSkill(std::wstring _path, Skill* _dst)
{
	Skill* current = _dst;

	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();		

		if (file.path().extension() == L"")
		{
			std::wstring dir = filepath + L"/";
			if (current != nullptr)
			{
				if (!current->textureKeyList.empty())
				{
					if (current->linkedSkill == nullptr)
					{
						current->linkedSkill = new Skill;
					}

					if (LoadSkill(dir, current->linkedSkill))
					{
						current->linkedSkill->user = user;
						current->linkedSkill->initialize();
						current = current->linkedSkill;
					}
				}
				else
				{
					if (LoadSkill(dir, current))
					{

					}
				}
			}
			else
			{
				current = new Skill;
				if (LoadSkill(dir, current))
				{
					current->user = user;
					current->initialize();
				}
			}
			
		}
		else
		{
			if (DXTextureManager::getInstance()->Load(filepath))
			{
				current->textureKeyList.push_back(filepath);
			}
		}
	}

	return true;
}

//bool SkillManager::LoadSkill_New(std::wstring _path, std::vector<Skill*>* _dst)
//{
//	std::filesystem::path path(_path);
//	for (auto& file : std::filesystem::directory_iterator(path))
//	{
//		std::wstring filename = file.path().filename();
//		std::wstring filepath = file.path();
//
//		if (file.path().extension() == L"")
//		{
//			Skill* newSkill = new Skill;
//			std::wstring dir = filepath + L"/";
//			
//			if (LoadSkill(dir, newSkill))
//			{
//				current = current->linkedSkill;
//			}
//				
//			}
//			else
//			{
//				current = new Skill;
//				if (LoadSkill(dir, current))
//				{
//
//				}
//			}
//
//		}
//		else
//		{
//			if (DXTextureManager::getInstance()->Load(filepath))
//			{
//				current->textureKeyList.push_back(filepath);
//			}
//		}
//	}
//
//	return true;
//}

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

bool SkillManager::activeSkill(std::wstring _name)
{
	Skill* targetSkill = getSkill(_name);
	if (targetSkill != nullptr)
	{
		bool isExist = false;
		for (auto it : activatedSkill)
		{
			if (it == targetSkill)
			{
				isExist = true;
				break;
			}
		}

		if (!isExist)
		{
			targetSkill->initialize();
			targetSkill->totalTime = 0.0f;
			activatedSkill.push_back(targetSkill);
		}
	}
	return true;
}

bool SkillManager::initialize()
{
	return true;
}

bool SkillManager::frame()
{
	for (auto it = activatedSkill.begin(); it != activatedSkill.end(); )
	{
		if ((*it)->isEnd && ((*it)->totalTime >= (*it)->coolTime))
		{
			it = activatedSkill.erase(it);
		}
		else
		{
			(*it)->frame();
		}

		if (it != activatedSkill.end())
		{
			it++;
		}
	}

	return true;
}

bool SkillManager::render()
{
	for (auto it : activatedSkill)
	{
		if (!it->isEnd)
		{
			it->render();
		}
	}

	return true;
}

bool SkillManager::release()
{
	activatedSkill.clear();
	return true;
}
