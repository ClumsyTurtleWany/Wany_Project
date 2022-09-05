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
		/*
		 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
		 * 0x3A - 0x40 : unassigned
		 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
		 */

		/*POINT ptPos = Input::getInstance()->m_ptPos;
		if (Input::getInstance()->getKey(VK_LBUTTON) == KeyState::Hold)
		{
			DXWriter::getInstance()->draw(ptPos.x, ptPos.y, L"Mouse LButton", D2D1_COLOR_F({ 1, 0, 0, 1 }));
		}
		if (Input::getInstance()->getKey(VK_SPACE) == KeyState::Hold)
		{
			DXWriter::getInstance()->draw(100, 300, L"Space", D2D1_COLOR_F({ 1, 0, 0, 1 }));
		}
		if (Input::getInstance()->getKey('W') == KeyState::Hold)
		{
			DXWriter::getInstance()->draw(100, 400, L"W Button", D2D1_COLOR_F({ 1, 0, 0, 1 }));
		}
		if (Input::getInstance()->getKey('A') == KeyState::Hold)
		{
			DXWriter::getInstance()->draw(100, 500, L"A Button", D2D1_COLOR_F({ 1, 0, 0, 1 }));
		}
		if (Input::getInstance()->getKey('S') == KeyState::Hold)
		{
			DXWriter::getInstance()->draw(100, 600, L"S Button", D2D1_COLOR_F({ 1, 0, 0, 1 }));
		}
		if (Input::getInstance()->getKey('D') == KeyState::Hold)
		{
			DXWriter::getInstance()->draw(100, 700, L"D Button", D2D1_COLOR_F({ 1, 0, 0, 1 }));
		}*/

		/*std::wstring lx = std::to_wstring(DXInput::getInstance()->m_MouseState.lX);
		std::wstring ly = std::to_wstring(DXInput::getInstance()->m_MouseState.lY);
		std::wstring lz = std::to_wstring(DXInput::getInstance()->m_MouseState.lZ);
		std::wstring mousePos = lx + L", " + ly + L", " + lz;
		DXWriter::getInstance()->draw(0, 300, mousePos, D2D1_COLOR_F({ 1, 0, 0, 1 }));*/
		
		return true;
	}

	bool release() override
	{
		
		return true;
	}
};

Engine* Engine::engine = nullptr;