#include "NPCState_Attack.hpp"
#include "NPCManager.hpp"
#include "DXTextureManager.hpp"
#include "Timer.hpp"
#include "NPCState_MoveRight.hpp"

NPCState_Attack::NPCState_Attack(NPC* _npc) : NPCState(_npc)
{
	initialize();
}

void NPCState_Attack::calcPos()
{
	float aspectRatio = 1.5f;
	float width = spriteList[state].width() * aspectRatio;
	float height = spriteList[state].height() * aspectRatio;
	float offset_x = spriteOffset.x * aspectRatio;
	float offset_y = spriteOffset.y * aspectRatio;
	
	float x = npc->currentDirection == NPC::Direction::Left ? 
		npc->shape.left() - offset_x : npc->shape.right() + offset_x - width;

	float y = npc->boundaryRect.bottom() + offset_y - height;
	npc->shape = Rect2f(x, y, width, height);

	//float hitbox_width = spriteHitboxList[state].width() * aspectRatio;
	//float hitbox_height = spriteHitboxList[state].height() * aspectRatio;
	//float hitboxOffset_x = (spriteHitboxList[state].LT.x - spriteList[state].LT.x) * aspectRatio;
	//float hitboxOffset_y = (spriteHitboxList[state].LT.y - spriteList[state].LT.y) * aspectRatio;
	//npc->hitbox = Rect2f(x + hitboxOffset_x, y + hitboxOffset_y, hitbox_width, hitbox_height);
	calcHitbox();
}

void NPCState_Attack::calcHitbox()
{
	float aspectRatio = 1.5f;
	float hitbox_width = spriteHitboxList[state].width() * aspectRatio;
	float hitbox_height = spriteHitboxList[state].height() * aspectRatio;
	float hitboxOffset_x = (spriteHitboxList[state].LT.x - spriteList[state].LT.x) * aspectRatio;
	float hitboxOffset_y = (spriteHitboxList[state].LT.y - spriteList[state].LT.y) * aspectRatio;

	npc->hitbox = npc->currentDirection == NPC::Direction::Left ? 
		Rect2f(npc->shape.LT.x + hitboxOffset_x, npc->shape.LT.y + hitboxOffset_y, hitbox_width, hitbox_height):
		Rect2f(npc->shape.RB.x - hitboxOffset_x - hitbox_width, npc->shape.LT.y + hitboxOffset_y, hitbox_width, hitbox_height);
}

bool NPCState_Attack::initialize()
{
	std::map<std::wstring, std::vector<std::wstring>> textureMap;
	NPCManager::getInstance()->getTextureKeyMap(npc->NPCName, textureMap);
	if (npc->info.renderType == NPCInfo::RenderType::Sprite)
	{
		auto it = textureMap.find(L"Sprite");
		if (it != textureMap.end())
		{
			if (!it->second.empty())
			{
				DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(it->second[0]);
				npc->setTexture(pTexture);
			}
		}

		std::map<std::wstring, std::vector<Rect2f>> spriteMap;
		NPCManager::getInstance()->getSpriteMap(npc->NPCName, spriteMap);
		auto iter = spriteMap.find(L"attack");
		if (iter != spriteMap.end())
		{
			spriteList.assign(iter->second.begin(), iter->second.end());
			npc->SpriteList.assign(iter->second.begin(), iter->second.end());
		}

		std::map<std::wstring, std::vector<Rect2f>> spriteHitboxMap;
		NPCManager::getInstance()->getSpriteHitboxMap(npc->NPCName, spriteHitboxMap);
		auto iterHitbox = spriteHitboxMap.find(L"attack");
		if (iterHitbox != spriteHitboxMap.end())
		{
			spriteHitboxList.assign(iterHitbox->second.begin(), iterHitbox->second.end());
		}

		std::map<std::wstring, Vector2f> spriteOffsetMap;
		NPCManager::getInstance()->getSpriteOffsetMap(npc->NPCName, spriteOffsetMap);
		auto iter2 = spriteOffsetMap.find(L"attack");
		if (iter2 != spriteOffsetMap.end())
		{
			spriteOffset = iter2->second;
		}

		beforePosition = npc->shape;
		calcPos();
	}
	else
	{
		auto it = textureMap.find(L"attack");
		if (it != textureMap.end())
		{
			if (!it->second.empty())
			{
				DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(it->second[0]);
				npc->setTexture(pTexture);
			}
			textureKeyList.assign(it->second.begin(), it->second.end());
		}
	}

	state = 0;
	npc->boundaryCheck = false;
	npc->SpriteNum = state;
	lifeTime = 2.5f + ((rand() % 250) / 100.0f);
	totalTime = 0.0f;
	beforeTime = Timer::getInstance()->getPlayTime();

	npc->force.x = 0.0f;
	npc->force.y = 0.0f;

	return true;
}

bool NPCState_Attack::frame()
{
	float currentTime = Timer::getInstance()->getPlayTime();
	float frameTime = currentTime - beforeTime;
	effectTime += frameTime;
	totalTime += frameTime;
	float nextFrame = (1000.0f / 60.0f) / 100.0f;
	if (effectTime >= nextFrame)
	{
		effectTime = 0.0f;

		if (npc->info.renderType == NPCInfo::RenderType::Sprite)
		{
			if (state < spriteList.size() - 1)
			{
				state++;
			}
			else
			{
				state = 0;
				npc->boundaryCheck = true;
				npc->shape = beforePosition;
				npc->changeCurrentState<NPCState_Idle>();
				return true;
			}

			//npc->pos = { npc->shape.left(), npc->shape.top() };
			//npc->shape = Rect2f(npc->pos.x, npc->pos.y, spriteList[state].width() * 1.5f, spriteList[state].height() * 1.5f);

			//float width = spriteList[state].width() * 1.5f;
			//float height = spriteList[state].height() * 1.5f;
			//
			//float x = npc->shape.left() - (width - npc->shape.width()) - spriteOffset.x;
			//float y = npc->shape.top() - (height - npc->shape.height()) - spriteOffset.y;
			//
			//npc->pos = { x, y };
			//npc->shape = Rect2f(npc->pos.x, npc->pos.y, width, height);
			//calcPos();
			calcHitbox();

			npc->SpriteNum = state;
		}
		else
		{
			if (state < textureKeyList.size() - 1)
			{
				state++;
			}
			else
			{
				state = 0;
				npc->boundaryCheck = true;
				npc->shape = beforePosition;
				npc->changeCurrentState<NPCState_Idle>();
				return true;
			}

			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(textureKeyList[state]);
			npc->setTexture(pTexture);
		}
	}
	beforeTime = currentTime;

	return true;
}

bool NPCState_Attack::render()
{
	//std::wstring strUserState;
	//strUserState += L"UserState: ";
	//strUserState += L"NPCState_Attack";
	//DXWriter::getInstance()->draw(0, 100, strUserState);

	return true;
}

bool NPCState_Attack::release()
{
	return true;
}