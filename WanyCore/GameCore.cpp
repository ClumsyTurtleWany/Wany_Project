#include "GameCore.hpp"

bool GameCore::CoreInitialize()
{
	if (DXDevice::initialize() == false)
	{
		return false;
	}
	Input::getInstance()->initialize();
	Timer::getInstance()->initialize();
	

	// DXWriter
	DXWriter::getInstance()->initialize();
	IDXGISurface* pBackBuffer;
	// Buffer를 Surface 타입으로 가져 올 것이다. 0번 버퍼의 복사본(pBackBuffer에) 생성.
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	DXWriter::getInstance()->setBuffer(pBackBuffer);
	pBackBuffer->Release();

	return initialize();
}

bool GameCore::CoreFrame()
{
	Input::getInstance()->frame();
	Timer::getInstance()->frame();

	DXWriter::getInstance()->frame();
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
	///////////////////////////////////
	// 여기서 랜더링 필요.
	render();
	Input::getInstance()->render();
	Timer::getInstance()->render();

	
	Timer* timer = Timer::getInstance();
	std::wstring info = L"Time: " + std::to_wstring(timer->getPlayTime()) + L", Fps: " + std::to_wstring(timer->getFPS()) + L"\n";
	DXWriter::getInstance()->setString(info);
	DXWriter::getInstance()->render();
	///////////////////////////////////
	PostRender();
	return true;
}

bool GameCore::CoreRelease()
{
	release();
	// initialize 역순으로 release 할 것!

	DXWriter::getInstance()->release();
	Input::getInstance()->release();
	Timer::getInstance()->release();
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