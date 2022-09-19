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

	DXShaderBorderManager::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);
	if (!DXShaderBorderManager::getInstance()->initialize())
	{
		OutputDebugString(L"WanyCore::DXShaderBorderManager::Failed Initialize.\n");
		return false;
	}

	if (!FMODSoundManager::getInstance()->initialize())
	{
		OutputDebugString(L"WanyCore::FMODSoundManager::Failed Initialize.\n");
		return false;
	}

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
		// Buffer�� Surface Ÿ������ ���� �� ���̴�. 0�� ������ ���纻(pBackBuffer��) ����.
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

	if (!FMODSoundManager::getInstance()->frame())
	{
		OutputDebugString(L"WanyCore::FMODSoundManager::Failed frame.\n");
		return false;
	}

	return frame();
}

bool GameCore::PreRender()
{
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // m_pRTV �� �Ѹ���.
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // R, G, B, A �� 0 ~ 1.0���� �� 1.0 == 255
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);

	// Sampler State ����.
	m_pImmediateContext->PSSetSamplers(0, 1, &DXSamplerState::pDefaultSamplerState);

	// Rasterizer State ����.
	//m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSWireFrame);

	// View Port ����
	// ������ client ũ��� ����������, �̴ϸ��� ��� ����Ʈ ������ �ٲ� ��� ����.
	//D3D11_VIEWPORT viewPort;
	//viewPort.TopLeftX = 0;
	//viewPort.TopLeftY = 0;
	//viewPort.Width = 1366; 
	//viewPort.Height = 786;
	//viewPort.MinDepth = 0;
	//viewPort.MaxDepth = 1;
	//m_pImmediateContext->RSSetViewports(0, &viewPort);

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

	if (!render())
	{
		OutputDebugString(L"WanyCore::GameCore::Failed Render.\n");
		return false;
	}

#ifdef DEBUG_DISPLAY
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
#endif
	///////////////////////////////////
	PostRender();
	return true;
}

bool GameCore::CoreRelease()
{
	release();
	// initialize �������� release �� ��!
	FMODSoundManager::getInstance()->release();	
	DXTextureManager::getInstance()->release();
	DXShaderBorderManager::getInstance()->release();
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