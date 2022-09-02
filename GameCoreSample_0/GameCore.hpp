#pragma once
#include "DXDevice.hpp"

class GameCore : public DXDevice
{
public:
	Timer m_Timer;


public:
	virtual bool initialize() { return true; };
	virtual bool frame() { return true; };
	virtual bool render() { return true; };
	virtual bool release() { return true; };

private:
	bool CoreInitialize();
	bool CoreFrame();
	bool CoreRender();
	bool CoreRelease();
	bool PreRender();
	bool PostRender();

public:
	bool run();
};



bool GameCore::CoreInitialize()
{
	if (DXDevice::initialize() == false)
	{
		return false;
	}
	m_Timer.initialize();
	return initialize();
}

bool GameCore::CoreFrame()
{
	m_Timer.frame();
	return frame();
}

bool GameCore::PreRender()
{
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // m_pRTV 에 뿌린다.
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // R, G, B, A 순 0 ~ 1.0사이 값 1.0 == 255
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
	return true;
}

bool GameCore::PostRender()
{
	m_pSwapChain->Present(0, 0); // 0번 버퍼를 뿌린다.
	return true;
}

bool GameCore::CoreRender()
{
	PreRender();

	// 여기서 삼각형 랜더링 필요.
	render();
	m_Timer.render();

	PostRender();
	return true;
}

bool GameCore::CoreRelease()
{
	release();
	m_Timer.release();
	DXDevice::release();
	
	return true;
}

bool GameCore::run()
{
	if (CoreInitialize())
	{
		bool bGameRun = true;
		while (bGameRun)
		{
			if (!WindowUI::run())
			{
				bGameRun = false;
			}
			else
			{
				CoreFrame();
				CoreRender();
			}
		}
		CoreRelease();

		return true;
	}
	else
	{
		return false;
	}
}