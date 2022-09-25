#include "SkillManager.hpp"
#include "DXTextureManager.hpp"

bool SkillManager::LoadDir(std::wstring _path)
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
			Skill* newSkill = new Skill;
			std::wstring dir = filepath + L"/";

			auto it = skillList.find(dir);
			if (it != skillList.end())
			{
				continue;
			}

			if (LoadSkill(dir, newSkill))
			{
				skillNameList.push_back(dir);
				skillList.insert(std::make_pair(dir, newSkill));
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
