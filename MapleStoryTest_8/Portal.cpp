#include "Portal.hpp"
#include "Scene_InGame.hpp"
#include "Timer.hpp"

Portal::Portal()
{
	mapObjectType = MapObjectType::Portal;
	createShader(ShaderType::Texture);
}

Portal::Portal(Rect2f _rect)
{
	shape = _rect;
	hitbox = Rect2f(shape.LT.x - 20.0f, shape.LT.y, shape.width() + 40.0f, shape.height());
	mapObjectType = MapObjectType::Portal;
	createShader(ShaderType::Texture);
}

bool Portal::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();

		if (DXTextureManager::getInstance()->Load(filepath))
		{
			textureKeyList.push_back(filepath);
		}
	}

	return true;
}

void Portal::setScene(Scene_InGame* _InGame)
{
	InGame = _InGame;
}

void Portal::setDstMap(std::wstring _name)
{
	dstMapName = _name;
}

void Portal::setDstPos(Vector2f _pos)
{
	dstPos = _pos;
}

bool Portal::RectInPortal(Rect2f _target)
{
	return hitbox.RectInRect(_target);
}

bool Portal::WarpPortal()
{
	return InGame->changeCurrentMap(dstMapName, dstPos);
}

bool Portal::initialize()
{
	MapObject::initialize();

	if (!Load(PORTAL_DIRECTORY))
	{
		return false;
	}

	state = 0;
	frameTime = (1000.0f / 60.0f) / 100.0f;
	timeCounter = 0.0f;
	beforeTime = Timer::getInstance()->getPlayTime();
	return false;
}

bool Portal::frame(float _dt)
{
	float currentTime = Timer::getInstance()->getPlayTime();
	float secondPerSecond = currentTime - beforeTime;
	timeCounter += secondPerSecond;
	beforeTime = currentTime;

	if (timeCounter >= frameTime)
	{
		timeCounter = 0.0f;

		if (state < textureKeyList.size() - 1)
		{
			state++;
		}
		else
		{
			state = 0;
		}

		pShader->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[state]));
		//shape = Rect2f(0, 0, pShader->getTextureWidth(), pShader->getTextureHeight());
		//moveCenterTo(pos);
	}
	return true;
}

bool Portal::render()
{
	object2D<float>::render();

	DrawBorder(hitbox, BORDER_COLOR_BLUE);

	return true;
}

bool Portal::release()
{
	return true;
}
