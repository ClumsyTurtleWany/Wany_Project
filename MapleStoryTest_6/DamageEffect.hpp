#pragma once
#include "Effect.hpp"

class DamageEffect : public Effect
{
public:
	int damage = 0;
	bool isMiss = false;
	bool isGaurd = false;
	bool isResist = false;
	float alphaBlendVal = 1.0f;

	std::map<std::wstring, std::wstring> textureKeyMap;

public:
	DamageEffect();
	DamageEffect(DamageEffect* _src);
	DamageEffect(const Rect2f& _rect);
	virtual ~DamageEffect();

public:
	virtual bool Load(std::wstring _path) override;
	virtual bool LoadInfo(std::wstring _path);
	virtual void setPos(Vector2f _pos);
	void setDamage(int _damage);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};