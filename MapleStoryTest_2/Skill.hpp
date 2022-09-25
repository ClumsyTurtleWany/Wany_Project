#pragma once
#include "Object.hpp"
#include "Camera.hpp"
#include "Player.hpp"

enum class SkillType
{
	Immediate,
	Combo,
	Keydown,
	Installation,
	Buff,
	Projectile,
};

class Skill : public object2D<float>
{
public:
	SkillType skillType = SkillType::Immediate;
	int state = 0;
	float beforeTime = 0.0f;
	float timeCounter = 0.0f;
	float effectTime = 0.0f;
	float frameTime = 0.0f;
	float coolTime = 0.0f;
	//float lifeTime = 0.0f;
	std::vector<std::wstring> textureKeyList;

	bool isCancle = false;

	Player* user = nullptr;

	Skill* linkedSkill = nullptr;

public:
	Skill();
	Skill(const Rect2f& _rect);
	virtual ~Skill();

public:
	void setCamera(Camera* _camera);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};