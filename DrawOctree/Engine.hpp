#pragma once
#include "Core.hpp"
#include "DXDevice.hpp"

class Engine : public DXDevice
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

	bool initialize() override
	{
		gameCore.setDevice(m_pd3dDevice, m_pImmediateContext);
		gameCore.initialize();
		return true;
	}

	bool frame() override
	{
		gameCore.frame(0.01);
		return true;
	}

	bool render() override
	{
		gameCore.render();
		return true;
	}

	bool release() override
	{
		return true;
	}
};

Engine* Engine::engine = nullptr;