#pragma once
#include "DXDevice.hpp"
#include "Input.hpp"
#include "Timer.hpp"
#include "DXWriter.hpp"

class GameCore : public DXDevice
{
public:
	DXWriter dxWriter;

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
	Timer::getInstance()->initialize();
	Input::getInstance()->initialize();
	Input::getInstance()->setWndHandle(this->hWnd);
	
	// DXWriter
	dxWriter.initialize();
	IDXGISurface* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer); // Buffer�� Surface�� ���� �� ���̴�.
	dxWriter.setBuffer(pBackBuffer);
	pBackBuffer->Release();

	return initialize();
}

bool GameCore::CoreFrame()
{
	Timer::getInstance()->frame();
	Input::getInstance()->frame();
	dxWriter.frame();
	return frame();
}

bool GameCore::PreRender()
{
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // m_pRTV �� �Ѹ���.
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // R, G, B, A �� 0 ~ 1.0���� �� 1.0 == 255
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
	return true;
}

bool GameCore::PostRender()
{
	m_pSwapChain->Present(0, 0); // 0�� ���۸� �Ѹ���.
	return true;
}

bool GameCore::CoreRender()
{
	PreRender();

	// ���⼭ �ﰢ�� ������ �ʿ�.
	render();
	Timer::getInstance()->render();
	Input::getInstance()->render();

	std::wstring fps = std::to_wstring(Timer::getInstance()->gameTime) + L" : " + std::to_wstring(Timer::getInstance()->fps);
	dxWriter.setString(fps);
	dxWriter.render();

	PostRender();
	return true;
}

bool GameCore::CoreRelease()
{
	release();
	Timer::getInstance()->release();
	Input::getInstance()->release();
	dxWriter.release();
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