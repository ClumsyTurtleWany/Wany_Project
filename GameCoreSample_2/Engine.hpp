#pragma once
#include "GameCore.hpp"

#include "QuadTree.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"

//#include "DXTextureManager.hpp"

class Engine : public GameCore
{
private:
	static Engine* engine;

	SpaceDivision*				worldMap = nullptr;
	object2D<float>*			worldMapObj = nullptr;
	objectBase*					user = nullptr;
	std::vector<objectBase*>	NPCList;
	std::vector<objectBase*>	ObstacleList;


private:
	Engine() {};
	~Engine() {};

public:
	static Engine* getEngine()
	{
		if (engine == nullptr)
		{
			engine = new Engine;
		}
		return engine;
	}
	
public:
	bool initialize() override
	{
		
		if (worldMap == nullptr)
		{
			worldMap = new QuadTree<float>;
			Rect_<float> region = Rect_<float>(0, 0, 128.0f, 128.0f);
			worldMap->create(&region);
		}
		if (worldMapObj == nullptr)
		{
			worldMapObj = new object2D<float>;
			worldMapObj->shape = Rect_<float>(0, 0, 1024, 768);
			worldMapObj->createShader(ShaderType::Normal);
			worldMapObj->setTexture(DXTextureManager::getInstance()->getTexture(Texture_Key::World));
		}

		if (user == nullptr)
		{
			user = worldMap->newPlayer();
			user->Random();
			user->createShader();
			user->setTexture(DXTextureManager::getInstance()->getTexture(Texture_Key::Charater));
			user->setTextureMask(DXTextureManager::getInstance()->getTextureMask(Texture_Key::Charater));
			user->setSpriteList(DXTextureManager::getInstance()->getSpriteList(Sprite_Key::Player));

		}

		return true;
	}

	bool frame() override
	{
		worldMap->checkBorder(user);
		user->frame(Timer::getInstance()->getDeltaTime());
		return true;
	}

	bool render() override
	{
		worldMapObj->render();
		user->render();
		
		return true;
	}

	bool release() override
	{
		
		return true;
	}
};

Engine* Engine::engine = nullptr;