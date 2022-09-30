#include "NPCState_MoveLeft.hpp"
#include "NPCManager.hpp"
#include "DXTextureManager.hpp"
#include "Timer.hpp"
#include "NPCState_MoveRight.hpp"

NPCState_MoveLeft::NPCState_MoveLeft(NPC* _npc) : NPCState(_npc)
{
	initialize();
}

bool NPCState_MoveLeft::initialize()
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
		auto iter = spriteMap.find(L"move");
		if (iter != spriteMap.end())
		{
			spriteList.assign(iter->second.begin(), iter->second.end());
			npc->SpriteList.assign(iter->second.begin(), iter->second.end());
		}

		std::map<std::wstring, Vector2f> spriteOffsetMap;
		NPCManager::getInstance()->getSpriteOffsetMap(npc->NPCName, spriteOffsetMap);
		auto iter2 = spriteOffsetMap.find(L"idle");
		if (iter2 != spriteOffsetMap.end())
		{
			spriteOffset = iter2->second;
		}
	}
	else
	{
		auto it = textureMap.find(L"move");
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
	npc->SpriteNum = state;
	lifeTime = 2.5f + ((rand() % 250) / 100.0f);
	totalTime = 0.0f;
	beforeTime = Timer::getInstance()->getPlayTime();

	//npc->force.x = -100.0f;
	//npc->force.y = 0.0f;

	return true;
}

bool NPCState_MoveLeft::frame()
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
			}

			//npc->pos = { npc->shape.left(), npc->shape.top() };
			//npc->shape = Rect2f(npc->pos.x, npc->pos.y, spriteList[state].width() * 1.5f, spriteList[state].height() * 1.5f);

			float width = spriteList[state].width() * 1.5f;
			float height = spriteList[state].height() * 1.5f;

			float x = npc->shape.left() - (width - npc->shape.width()) - spriteOffset.x;
			float y = npc->shape.top() - (height - npc->shape.height()) - spriteOffset.y;

			npc->pos = { x, y };
			npc->shape = Rect2f(npc->pos.x, npc->pos.y, width, height);

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
			}

			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(textureKeyList[state]);
			npc->setTexture(pTexture);
		}

		if (npc->currentDirection != NPC::Direction::Left)
		{
			npc->currentDirection = NPC::Direction::Left;
			npc->flipSprite(true);
			//npc->flipSpriteHorizontal();
		}
		else
		{
			npc->force.x = -100;
		}

		if (totalTime >= lifeTime)
		{
			totalTime = 0;
			int randomState = rand() % 3;

			if (randomState == 0)
			{
				npc->changeCurrentState<NPCState_Idle>();
				return true;
			}
			else if (randomState == 1)
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
	beforeTime = currentTime;

	return true;
}

bool NPCState_MoveLeft::render()
{
	//std::wstring strUserState;
	//strUserState += L"UserState: ";
	//strUserState += L"NPCState_MoveLeft";
	//DXWriter::getInstance()->draw(0, 100, strUserState);

	return true;
}

bool NPCState_MoveLeft::release()
{
	return true;
}