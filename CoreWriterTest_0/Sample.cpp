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
    DXWriter::getInstance()->initialize();
    IDXGISurface* pBackBuffer;
    m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer); // Buffer를 Surface로 가져 올 것이다.
    DXWriter::getInstance()->setBuffer(pBackBuffer);
    return true;
}

bool Sample::frame()
{
    Timer* timer = Timer::getInstance();
    std::wstring info = L"Time: " + std::to_wstring(timer->getPlayTime()) + L", Fps: " + std::to_wstring(timer->getFPS()) + L"\n";
    DXWriter::getInstance()->setString(info);
    return true;
}

bool Sample::render()
{
    DXWriter::getInstance()->render();
    return true;
}

bool Sample::release()
{
    DXWriter::getInstance()->release();
    return true;
}