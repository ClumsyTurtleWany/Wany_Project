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
	std::wstring skillName;

	SkillType skillType = SkillType::Immediate;
	float coolTime = 0.0f;
	std::vector<float> damage;
	bool isCancel = false;

	Player* user = nullptr;

	int childState = 0;
	std::vector<Skill*> childList;

public:
	Skill();
	Skill(const Rect2f& _rect);
	virtual ~Skill();

public:
	virtual bool Load(std::wstring _path) override;
	bool isCoolDown();

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};