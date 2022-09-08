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
    Background = new object2D<float>;
    Background->Random();
    Background->createShader(ShaderType::Normal);
    if (DXTextureManager::getInstance()->Load(RSRC_BACKGROUND))
    {
        Background->setTexture(DXTextureManager::getInstance()->getTexture(RSRC_BACKGROUND));
    }

    return true;
}

bool Sample::frame()
{
    Background->frame();
    return true;
}

bool Sample::render()
{
    Background->render();
    return true;
}

bool Sample::release()
{
    return true;
}