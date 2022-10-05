#pragma once
#include "Player.hpp"
#include "Effect.hpp"

enum class SkillType
{
	Immediate,
	Combo,
	Keydown,
	Installation,
	Buff,
	Projectile,
	Passive,
	Probabilistic,
};

class Skill : public Effect
{
public:
	bool isCancel = false;

	std::wstring skillName;
	SkillType skillType = SkillType::Immediate;
	
	Player* user = nullptr;
	
	std::vector<float> damageList;
	std::vector<Skill*> childList;
	int childState = 0;
	float coolTime = 0.0f;
	float requiredMP = 0.0f;
	int hitState = 0;
	
	Vector2f offset;
	Vector2f offset_hitbox;

public:
	Skill();
	Skill(Skill* _src);
	Skill(const Rect2f& _rect);
	virtual ~Skill();

private:
	Vector2f calcSkillPos();

public:
	virtual bool Load(std::wstring _path) override;
	virtual bool LoadInfo(std::wstring _path) override;
	bool isCoolDown();

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};