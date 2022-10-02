#include "NPCState_Search.hpp"
#include "NPCManager.hpp"
#include "DXTextureManager.hpp"
#include "Timer.hpp"
#include "NPCState_MoveLeft.hpp"
#include "NPCState_MoveRight.hpp"
#include "NPCState_Attack.hpp"
#include "NPCState_Die.hpp"

NPCState_Search::NPCState_Search(NPC* _npc) : NPCState(_npc)
{
	initialize();
}

void NPCState_Search::calcPos()
{
	float aspectRatio = 1.5f;
	float width = spriteList[state].width() * aspectRatio;
	float height = spriteList[state].height() * aspectRatio;
	float offset_x = spriteOffset.x * aspectRatio;
	float offset_y = spriteOffset.y * aspectRatio;
	float x = npc->shape.cx() - (width * 0.5f) - offset_x;
	float y = npc->boundaryRect.bottom() - height + offset_y;
	npc->shape = Rect2f(x, y, width, height);

	float hitbox_width = spriteHitboxList[state].width() * aspectRatio;
	float hitbox_height = spriteHitboxList[state].height() * aspectRatio;
	float hitboxOffset_x = (spriteHitboxList[state].LT.x - spriteList[state].LT.x) * aspectRatio;
	float hitboxOffset_y = (spriteHitboxList[state].LT.y - spriteList[state].LT.y) * aspectRatio;
	npc->hitbox = Rect2f(x + hitboxOffset_x, y + hitboxOffset_y, hitbox_width, hitbox_height);
}

bool NPCState_Search::initialize()
{
	lifeTime = 10.0f;
	totalTime = 0.0f;
	beforeTime = Timer::getInstance()->getPlayTime();

	return true;
}

bool NPCState_Search::frame()
{
	float currentTime = Timer::getInstance()->getPlayTime();
	float frameTime = currentTime - beforeTime;
	effectTime += frameTime;
	totalTime += frameTime;
	float nextFrame = (1000.0f / 60.0f) / 100.0f;
	if (effectTime >= nextFrame)
	{
		effectTime = 0.0f;

		if (npc->aggroTarget != nullptr)
		{
			Player* pTarget = npc->aggroTarget;
			float searchDistance = 400.0f;
			float x = npc->hitbox.LT.x - searchDistance;
			float y = npc->hitbox.LT.y;
			float width = npc->hitbox.width() + searchDistance * 2.0f;
			float height = npc->hitbox.height();
			Rect2f searchArea(x, y, width, height);
			DrawBorder(searchArea, BORDER_COLOR_RED);

			if (searchArea.intersectRect(pTarget->hitbox))
			{
				Player* pTarget = npc->aggroTarget;
				searchDistance = 100.0f;
				x = npc->hitbox.LT.x - searchDistance;
				y = npc->hitbox.LT.y;
				width = npc->hitbox.width() + searchDistance * 2.0f;
				height = npc->hitbox.height();
				Rect2f attackArea(x, y, width, height);
				DrawBorder(attackArea, BORDER_COLOR_RED);

				if (attackArea.intersectRect(pTarget->hitbox))
				{
					npc->changeCurrentState<NPCState_Attack>();
					return true;
				}
				else
				{
					if (pTarget->hitbox.cx() < npc->hitbox.cx())
					{
						npc->changeCurrentState<NPCState_MoveLeft>();
						return true;
					}
					else
					{
						npc->changeCurrentState<NPCState_MoveRight>();
						return true;
					}
				}
			}
			else
			{
				npc->aggroTarget = nullptr;
				npc->changeCurrentState<NPCState_Idle>();
				return true;
			}
		}
		else
		{
			npc->changeCurrentState<NPCState_Idle>();
			return true;
		}
	}
	beforeTime = currentTime;

	return true;
}

bool NPCState_Search::render()
{
	//std::wstring strUserState;
	//strUserState += L"UserState: ";
	//strUserState += L"NPCState_Search";
	//DXWriter::getInstance()->draw(0, 100, strUserState);

	return true;
}

bool NPCState_Search::release()
{
	return true;
}