#include "GameCore.hpp"

bool GameCore::CoreInitialize()
{
	if (!DXDevice::initialize())
	{
		OutputDebugString(L"WanyCore::DXDevice::Failed Initialize.\n");
		return false;
	}

	if (!Input::getInstance()->initialize())
	{
		OutputDebugString(L"WanyCore::Input::Failed Initialize.\n");
		return false;
	}

	if (!Timer::getInstance()->initialize())
	{
		OutputDebugString(L"WanyCore::Timer::Failed Initialize.\n");
		return false;
	}
	
	DXShaderManager::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);
	DXTextureManager::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);

	// Sampler State
	if (!DXSamplerState::setState(m_pd3dDevice))
	{
		OutputDebugString(L"WanyCore::DXSamplerState::Failed Set State.\n");
		return false;
	}


	// DXWriter
	if (!DXWriter::getInstance()->initialize())
	{
		OutputDebugString(L"WanyCore::DXWriter::Failed Initialize.\n");
		return false;
	}
	else
	{
		IDXGISurface* pBackBuffer;
		// Buffer를 Surface 타입으로 가져 올 것이다. 0번 버퍼의 복사본(pBackBuffer에) 생성.
		HRESULT rst = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
		if (SUCCEEDED(rst))
		{
			if (!DXWriter::getInstance()->setBuffer(pBackBuffer))
			{
				OutputDebugString(L"WanyCore::DXWriter::Failed Set Buffer.\n");
				return false;
			}
			pBackBuffer->Release();
		}
	}

	return initialize();
}

bool GameCore::CoreFrame()
{
	if (!Input::getInstance()->frame())
	{
		OutputDebugString(L"WanyCore::Input::Failed Frame.\n");
		return false;
	}

	if (!Timer::getInstance()->frame())
	{
		OutputDebugString(L"WanyCore::Timer::Failed Frame.\n");
		return false;
	}

	if (!DXWriter::getInstance()->frame())
	{
		OutputDebugString(L"WanyCore::DXWriter::Failed Frame.\n");
		return false;
	}

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
	///////////////////////////////////
	// 여기서 랜더링 필요.

	if (!render())
	{
		OutputDebugString(L"WanyCore::GameCore::Failed Render.\n");
		return false;
	}

	if (!Input::getInstance()->render())
	{
		OutputDebugString(L"WanyCore::Input::Failed Render.\n");
		return false;
	}

	if (!Timer::getInstance()->render())
	{
		OutputDebugString(L"WanyCore::Timer::Failed Render.\n");
		return false;
	}


	Timer* timer = Timer::getInstance();
	std::wstring info = L"Time: " + std::to_wstring(timer->getPlayTime()) + L", Fps: " + std::to_wstring(timer->getFPS()) + L"\n";
	DXWriter::getInstance()->setString(info);
	
	if (!DXWriter::getInstance()->render())
	{
		OutputDebugString(L"WanyCore::DXWriter::Failed Render.\n");
		return false;
	}
	///////////////////////////////////
	PostRender();
	return true;
}

bool GameCore::CoreRelease()
{
	release();
	// initialize 역순으로 release 할 것!

	DXTextureManager::getInstance()->release();
	DXShaderManager::getInstance()->release();
	DXSamplerState::release();
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