#pragma once
#include "NPCState_Idle.hpp"

class NPCState_Attack : public NPCState
{
public:
	std::vector<std::wstring> textureKeyList;
	std::vector<Rect2f> spriteList;
	std::vector<Rect2f> spriteHitboxList;
	Vector2f spriteOffset;

	int state = 0;

	float beforeTime = 0.0f;
	float effectTime = 0.0f;
	float totalTime = 0.0f;
	float lifeTime = 0.0f;

public:
	NPCState_Attack(NPC* _npc);

private:
	void calcPos();

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};
