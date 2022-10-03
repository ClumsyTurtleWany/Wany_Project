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
	std::vector<Skill*> jobList;

	Player* user = nullptr;

public:
	void setUser(Player* _user);
	bool Load(std::wstring _path);
	Skill* getSkill(std::wstring _name);

	bool addSkillToJobList(std::wstring _name);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

};