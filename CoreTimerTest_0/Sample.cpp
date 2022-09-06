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
    Timer::getInstance()->initialize();
    return true;
}

bool Sample::frame()
{
    Timer::getInstance()->frame();
    return true;
}

bool Sample::render()
{
    Timer::getInstance()->render();
    return true;
}

bool Sample::release()
{
    Timer::getInstance()->release();
    return true;
}