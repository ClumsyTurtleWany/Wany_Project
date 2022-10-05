#pragma once
#include "Effect.hpp"
#include <filesystem>
#include "DamageEffect.hpp"

class EffectManager : public Singleton<EffectManager>
{
private:
	friend class Singleton<EffectManager>;

private:
	std::map<std::wstring, std::unique_ptr<Effect>> effectList;
	std::vector<Effect*> jobList;
	std::map<std::wstring, std::unique_ptr<DamageEffect>> damageEffectList;

	Camera* renderCamera;

public:
	bool Load(std::wstring _path);
	bool LoadDamageEffect(std::wstring _path);
	void setCamera(Camera* _camera);
	bool addEffectToJobList(Vector2f _pos, std::wstring _name);
	bool addDamageEffectToJobList(Vector2f _pos, std::wstring _name, float _damage);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};