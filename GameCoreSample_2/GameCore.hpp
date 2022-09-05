#pragma once

#include "Timer.hpp"
#include "Input.hpp"
#include "DXDevice.hpp"
#include "DXInput.hpp"
#include "DXWriter.hpp"
#include "DXShaderManager.hpp"
#include "DXTextureManager.hpp"
#include "DXSamplerState.hpp"

class GameCore : public DXDevice
{

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
	//DXInput::getInstance()->setInstance(this->hInstance);
	//DXInput::getInstance()->setWndHandle(this->hWnd);
	//DXInput::getInstance()->initialize();

	DXTextureManager::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);
	DXTextureManager::getInstance()->initialize();

	DXShaderManager::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);

	// Sampler State
	DXSamplerState::setState(m_pd3dDevice);
	
	// DXWriter
	DXWriter::getInstance()->initialize();
	IDXGISurface* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer); // Buffer를 Surface로 가져 올 것이다.
	DXWriter::getInstance()->setBuffer(pBackBuffer);
	pBackBuffer->Release();

	return initialize();
}

bool GameCore::CoreFrame()
{
	Timer::getInstance()->frame();
	Input::getInstance()->frame();
	//DXInput::getInstance()->frame();
	DXWriter::getInstance()->frame();
	return frame();
}

bool GameCore::PreRender()
{
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // m_pRTV 에 뿌린다.
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // R, G, B, A 순 0 ~ 1.0사이 값 1.0 == 255
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);

	// Sampler State 적용.
	m_pImmediateContext->PSSetSamplers(0, 1, &DXSamplerState::pDefaultSamplerState);

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

	// 여기서 랜더링 필요.
	render();
	Timer::getInstance()->render();
	Input::getInstance()->render();
	//DXInput::getInstance()->render();

	std::wstring fps = std::to_wstring(Timer::getInstance()->gameTime) + L" : " + std::to_wstring(Timer::getInstance()->fps);
	DXWriter::getInstance()->setString(fps);
	DXWriter::getInstance()->render();

	PostRender();
	return true;
}

bool GameCore::CoreRelease()
{
	release();
	DXSamplerState::release();
	Timer::getInstance()->release();
	Input::getInstance()->release();
	//DXInput::getInstance()->release();
	DXWriter::getInstance()->release();
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