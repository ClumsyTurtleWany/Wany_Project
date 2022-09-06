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
    Input::getInstance()->initialize();
    return true;
}

bool Sample::frame()
{
    Input::getInstance()->frame();
    if (Input::getInstance()->getKey('W') != KeyState::Free)
    {
        int a = 0;
    }
    if (Input::getInstance()->getKey('A') != KeyState::Free)
    {
        int a = 0;
    }
    if (Input::getInstance()->getKey('S') != KeyState::Free)
    {
        int a = 0;
    }
    if (Input::getInstance()->getKey('D') != KeyState::Free)
    {
        int a = 0;
    }
    return true;
}

bool Sample::render()
{
    Input::getInstance()->render();
    return true;
}

bool Sample::release()
{
    Input::getInstance()->release();
    return true;
}