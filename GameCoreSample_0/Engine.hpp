#pragma once
#include "GameCore.hpp"

//#include "DXTextureManager.hpp"

class Engine : public GameCore
{
private:
	static Engine* engine;

	
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
		
		return true;
	}

	bool frame() override
	{
		
		return true;
	}

	bool render() override
	{
		
		return true;
	}

	bool release() override
	{
		
		return true;
	}
};

Engine* Engine::engine = nullptr;