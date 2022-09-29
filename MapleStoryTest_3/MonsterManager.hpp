#pragma once
#include "Monster.hpp"
#include <filesystem>

class MonsterManager : public Singleton<MonsterManager>
{
private:
	friend class Singleton<MonsterManager>;

private:
	std::map<std::wstring, std::unique_ptr<Monster>> monsterList;
	std::vector<Monster*> jobList;

	Camera* renderCamera;

public:
	bool Load(std::wstring _path);
	void setCamera(Camera* _camera);
	Monster* getMonster(std::wstring _name);
	bool addMonsterToJobList(Vector2f _pos, std::wstring _name);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};