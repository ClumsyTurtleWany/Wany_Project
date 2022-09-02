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
		/*
		 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
		 * 0x3A - 0x40 : unassigned
		 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
		 */
		POINT ptPos = Input::getInstance()->m_ptPos;
		if (Input::getInstance()->getKey(VK_LBUTTON) == KeyState::Push)
		{
			int a = 0;
		}
		if (Input::getInstance()->getKey(VK_LBUTTON) == KeyState::Up)
		{						
			int a = 0;			
		}						
		if (Input::getInstance()->getKey(VK_SPACE) == KeyState::Push)
		{						
			int a = 0;			
		}						
		if (Input::getInstance()->getKey('w') == KeyState::Push)
		{						
			int a = 0;			
		}						
		if (Input::getInstance()->getKey('a') == KeyState::Push)
		{						
			int a = 0;			
		}						
		if (Input::getInstance()->getKey('s') == KeyState::Push)
		{						
			int a = 0;			
		}						
		if (Input::getInstance()->getKey('d') == KeyState::Push)
		{
			int a = 0;
		}
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