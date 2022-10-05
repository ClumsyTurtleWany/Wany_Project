#include "Scene_Title.hpp"
#include "Scene_InGame.hpp"
#include "MapleStory.h"
#include "FMODSoundManager.hpp"

Scene_Title::Scene_Title(MapleStory* _game) : Scene(_game)
{
	initialize();
}

bool Scene_Title::initialize()
{
	RECT rectClient = g_pWindow->getClientRect();
	Vector2f centerPos;
	centerPos.x = (rectClient.right - rectClient.left) * 0.5f;
	centerPos.y = (rectClient.bottom - rectClient.top) * 0.5f;
	titleEffect = new Effect;
	titleEffect->Load(TITLE_DIRECTORY);
	titleEffect->setPos(centerPos);
	titleEffect->initialize();

	BGM = FMODSoundManager::getInstance()->getSound(L"Title.mp3");
	if (BGM != nullptr)
	{
		BGM->play();
	}
	return true;
}

bool Scene_Title::frame()
{
	if (!titleEffect->isEnd)
	{
		titleEffect->frame();
	}

	if (Input::getInstance()->isPressedAnyKey())
	{
		BGM->stop();
		game->changeCurrentScene<Scene_InGame>();
	}

	return true;
}

bool Scene_Title::render()
{
	titleEffect->render();
	return true;
}

bool Scene_Title::release()
{
	if (titleEffect != nullptr)
	{
		delete titleEffect;
		titleEffect = nullptr;
	}
	return false;
}

