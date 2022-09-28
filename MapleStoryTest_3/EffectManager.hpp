#pragma once
#include "Effect.hpp"
#include <filesystem>

class EffectManager : public Singleton<EffectManager>
{
private:
	friend class Singleton<EffectManager>;

private:
	std::map<std::wstring, std::unique_ptr<Effect>> effectList;
	std::vector<Effect*> jobList;

public:
	bool Load(std::wstring _path);
	bool addEffectToJobList(Vector2f _pos, std::wstring _name);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};