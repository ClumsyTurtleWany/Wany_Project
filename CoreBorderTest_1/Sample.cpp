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
    return true;
}

bool Sample::frame()
{
    return true;
}

bool Sample::render()
{
    DXShaderBorderManager::getInstance()->drawBorder(Rect2f(0, 0, 100, 100), BORDER_COLOR_BLUE);
    DXShaderBorderManager::getInstance()->drawBorder(Rect2f(100, 100, 100, 100), Vector3f(0.0f, 1.0f, 0.0f));
    DXShaderBorderManager::getInstance()->drawBorder(Rect2f(200, 200, 100, 100), BORDER_COLOR_GREEN);
    DXShaderBorderManager::getInstance()->drawBorder(Rect2f(300, 300, 100, 100), BORDER_COLOR_RED);

    DrawBorder(Rect2f(400, 400, 200, 200), BORDER_COLOR_RED);
    DrawBorder(Rect2f(450, 450, 200, 200), Vector3f(0.0f, 1.0f, 0.0f));

    return true;
}

bool Sample::release()
{
    return true;
}