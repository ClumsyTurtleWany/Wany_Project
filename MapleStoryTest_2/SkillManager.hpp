#pragma once
#include "Define.hpp"
#include "Resource.h"
#include "Skill.hpp"

class SkillManager : public Singleton<SkillManager>
{
private:
	friend class Singleton<SkillManager>;

private:
	std::map<std::wstring, Skill*> skillList;

public:
	std::vector<std::wstring> skillNameList;

private:
	bool LoadSkill(std::wstring _path, Skill* _dst);

public:
	bool LoadDir(std::wstring _path);
	Skill* getSkill(std::wstring _name);

};