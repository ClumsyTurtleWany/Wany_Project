#pragma once
#include "Skill.hpp"

class Effect : public object2D<float>
{
public:
	int state = 0;
	float beforeTime = 0.0f;
	float timeCounter = 0.0f;
	float effectTime = 0.0f;
	float frameTime = 0.0f;
	float lifeTime = 0.0f;
	std::vector<std::wstring> textureKeyList;

public:
	Effect();
	Effect(const Rect2f& _rect);
	virtual ~Effect();

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};