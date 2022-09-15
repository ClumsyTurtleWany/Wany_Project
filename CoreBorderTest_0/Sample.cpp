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
    DXShaderBorderManager::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);
    DXShaderBorderManager::getInstance()->initialize();

    return true;
}

bool Sample::frame()
{
    return true;
}

bool Sample::render()
{
    DXShaderBorderManager::getInstance()->drawBorder(Rect2f(0, 0, 100, 100), BORDER_COLOR_BLUE);
    DXShaderBorderManager::getInstance()->drawBorder(Rect2f(100, 100, 100, 100), BORDER_COLOR_RED);
    DXShaderBorderManager::getInstance()->drawBorder(Rect2f(200, 200, 100, 100), BORDER_COLOR_GREEN);
    DXShaderBorderManager::getInstance()->drawBorder(Rect2f(300, 300, 100, 100), BORDER_COLOR_RED);
    return true;
}

bool Sample::release()
{
    DXShaderBorderManager::getInstance()->release();
    return true;
}