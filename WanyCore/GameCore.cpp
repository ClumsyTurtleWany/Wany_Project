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
	// Buffer�� Surface Ÿ������ ���� �� ���̴�. 0�� ������ ���纻(pBackBuffer��) ����.
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
	///////////////////////////////////
	// ���⼭ ������ �ʿ�.
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
	// initialize �������� release �� ��!

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