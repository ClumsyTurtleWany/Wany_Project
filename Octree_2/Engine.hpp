#pragma once
#include "Core2D.hpp"
#include "Core3D.hpp"

class Engine
{
private:
	static Engine* engine;

private:
	Core* gameCore = nullptr;

private:
	Engine() {};
	~Engine() {};

public:
	static Engine* getEngine(CORE_TYPE _type = CORE_TYPE::GAME_3D)
	{
		if (engine == nullptr)
		{
			engine = new Engine;
			if (engine->gameCore == nullptr)
			{
				if (_type == CORE_TYPE::GAME_2D)
				{
					engine->gameCore = new Core2D;
				}
				else if (_type == CORE_TYPE::GAME_3D)
				{
					engine->gameCore = new Core3D;
				}
				else
				{
					engine->gameCore = nullptr;
				}
			}
		}
		return engine;
	}
	
	Core* getCore()
	{
		return gameCore;
	}

	void release()
	{
		if (gameCore != nullptr)
		{
			delete gameCore;
			gameCore = nullptr;
		}
	}
};

Engine* Engine::engine = nullptr;