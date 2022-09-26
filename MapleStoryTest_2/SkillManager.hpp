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
	std::map<std::wstring, std::vector<Skill*>> skillVectorList;
	std::vector<Skill*> activatedSkill;

	Player* user = nullptr;

public:
	std::vector<std::wstring> skillNameList;

private:
	bool LoadSkill(std::wstring _path, Skill* _dst);
	//bool LoadSkill_New(std::wstring _path, std::vector<Skill*>* _dst);

public:
	void setUser(Player* _user);
	bool LoadDir(std::wstring _path);
	//bool LoadDir_New(std::wstring _path);
	Skill* getSkill(std::wstring _name);
	bool activeSkill(std::wstring _name);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

};