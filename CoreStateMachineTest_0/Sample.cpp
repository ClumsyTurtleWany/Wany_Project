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
    user = new Player();
    return true;
}

bool Sample::frame()
{
    user->frame(Timer::getInstance()->getDeltaTime());
    return true;
}

bool Sample::render()
{
    user->render();
    return true;
}

bool Sample::release()
{
    return true;
}