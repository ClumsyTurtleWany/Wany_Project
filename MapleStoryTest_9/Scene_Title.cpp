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
	float clientWidth = g_pWindow->getClientWidth();
	float clientHeight = g_pWindow->getClientHeight();

	titleBackground = new object2D<float>;
	titleBackground->createShader(ShaderType::Texture);
	titleBackground->shape = Rect2f(0.0f, 0.0f, clientWidth, clientHeight);
	if (DXTextureManager::getInstance()->Load(TITLE_BACKGROUND))
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(TITLE_BACKGROUND);
		titleBackground->setTexture(pTexture);
	}

	BGM = FMODSoundManager::getInstance()->getSound(L"Title.mp3");
	if (BGM != nullptr)
	{
		BGM->setVolume(0.5f);
		BGM->play();
	}
	return true;
}

bool Scene_Title::frame()
{
	/*if (!titleEffect->isEnd)
	{
		titleEffect->frame();
	}*/
	alpha = 1.0f + (cos(Timer::getInstance()->getPlayTime()) * 0.7f);

	if (Input::getInstance()->isPressedAnyKey())
	{
		//BGM->stop();
		//game->changeCurrentScene<Scene_InGame>();
		return true;
	}

	return true;
}

bool Scene_Title::render()
{
	titleBackground->render();
	
	DXWriter::getInstance()->draw(570, 550, L"Press Any Key to Continue...", D2D1_COLOR_F({ 1.0f, 1.0f, 1.0f, 1.0f }), alpha);

	return true;
}

bool Scene_Title::release()
{
	if (titleBackground != nullptr)
	{
		delete titleBackground;
		titleBackground = nullptr;
	}
	return true;
}

