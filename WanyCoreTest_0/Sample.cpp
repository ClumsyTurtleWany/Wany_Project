#include "Sample.h"

// 2022-09-06

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample sampleWindow;
    sampleWindow.createWindow(hInstance, L"TestName", 1024, 768);
    sampleWindow.run();

    return 1;
}



bool Sample::initialize()
{
    DXDevice::initialize();
    return true;
}

bool Sample::frame()
{
    DXDevice::frame();
    return true;
}

bool Sample::render()
{
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // m_pRTV 에 뿌린다. (Render Target View)
    float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // R, G, B, A 순 0 ~ 1.0사이 값 1.0 == 255
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);

    m_pSwapChain->Present(0, 0); // 0번 버퍼를 뿌린다.

    return true;
}

bool Sample::release()
{
    DXDevice::release();
    return true;
}


bool Sample::run()
{
    initialize();
    bool bRun = true;
    while (bRun)
    {
        if (WindowUI::run())
        {
            frame();
            render();
        }
        else
        {
            bRun = false;
        }
    }
    
    release();

    return true;
}
