#pragma once
#include "Core.hpp"

class Engine
{
private:
	static Engine* engine;

private:
	Core gameCore;

private:
	Engine() {};
	~Engine() {};

public:
	static Engine* getEngine(CORE_TYPE _type = CORE_TYPE::GAME_3D)
	{
		if (engine == nullptr)
		{
			engine = new Engine;
			
			if (_type == CORE_TYPE::GAME_2D)
			{
				engine->gameCore.map = new QuadTree<float>;
				Rect_<float> region = Rect_<float>(0, 0, 128.0f, 128.0f);
				engine->gameCore.map->create(&region);
				
			}
			else if (_type == CORE_TYPE::GAME_3D)
			{
				engine->gameCore.map = new Octree<float>;
				Box_<float> region = Box_<float>(Point3D_<float>(0.0f, 0.0f, 0.0f), 128.0f, 128.0f, 128.0f);
				engine->gameCore.map->create(&region);
			}
			else
			{
				engine->gameCore.map = nullptr;
			}
			
		}
		return engine;
	}
	
	Core* getCore()
	{
		return &gameCore;
	}

	void release()
	{
	}
};

Engine* Engine::engine = nullptr;