#pragma once
#include "Core.hpp"

class Engine
{
private:
	static Engine* engine;

private:
	CoreBase* gameCore = nullptr;

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
					engine->gameCore = new Core<Rect_<float>, object2D<float>>;
					SpaceDivision<Rect_<float>, object2D<float>>* map = (SpaceDivision<Rect_<float>, object2D<float>>*)engine->gameCore->getMap();
					map = new QuadTree<float>;
					map->create(Rect_<float>(0, 0, 128.0f, 128.0f));
				}
				else if (_type == CORE_TYPE::GAME_3D)
				{
					engine->gameCore = new Core<Box_<float>, object3D<float>>;
					SpaceDivision<Box_<float>, object3D<float>>* map = (SpaceDivision<Box_<float>, object3D<float>>*)engine->gameCore->getMap();
					map = new Octree<float>;
					map->create(Box_<float>(Point3D_<float>(0.0f, 0.0f, 0.0f), 128.0f, 128.0f, 128.0f));
				}
				else
				{
					engine->gameCore = nullptr;
				}
			}
		}
		return engine;
	}
	
	CoreBase* getCore()
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