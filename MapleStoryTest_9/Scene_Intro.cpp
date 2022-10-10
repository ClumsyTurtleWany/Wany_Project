#include "Scene_Intro.hpp"
#include "Scene_InGame.hpp"
#include "MapleStory.h"
#include "FMODSoundManager.hpp"
#include "Scene_Title.hpp"

Scene_Intro::Scene_Intro(MapleStory* _game) : Scene(_game)
{
	initialize();
}

bool Scene_Intro::initialize()
{
	RECT rectClient = g_pWindow->getClientRect();
	Vector2f centerPos;
	centerPos.x = (rectClient.right - rectClient.left) * 0.5f;
	centerPos.y = (rectClient.bottom - rectClient.top) * 0.5f;
	introEffect = new Effect;
	introEffect->Load(INTRO_DIRECTORY);
	introEffect->setPos(centerPos);
	introEffect->initialize();	

	FMODSound* pSound = FMODSoundManager::getInstance()->getSound(L"NxLogo.mp3");
	if (pSound != nullptr)
	{
		pSound->setVolume(0.5f);
		pSound->playEffect();
	}

	return true;
}

bool Scene_Intro::frame()
{
	if (!introEffect->isEnd)
	{
		introEffect->frame();
	}
	else
	{
		game->changeCurrentScene<Scene_Title>();
	}

	return true;
}

bool Scene_Intro::render()
{
	introEffect->render();
	return true;
}

bool Scene_Intro::release()
{
	if (introEffect != nullptr)
	{
		delete introEffect;
		introEffect = nullptr;
	}
	return false;
}

