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
    DXTextureManager::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);

    DXTextureManager* textureManager = DXTextureManager::getInstance();
    if (!textureManager->Load(RSRC_BACKGROUND))
    {
        OutputDebugString(L"Sample::initialize::Failed Load File.\n");
        return false;
    }

    if (!textureManager->Load(RSRC_CHARATER))
    {
        OutputDebugString(L"Sample::initialize::Failed Load File.\n");
        return false;
    }

    testShader.setDevice(m_pd3dDevice, m_pImmediateContext);
    testShader.setShaderFile(SHADER_FILE);
    testShader.initialize();


    return true;
}

bool Sample::frame()
{
    int time = static_cast<int>(Timer::getInstance()->getPlayTime());
    if ((time % 2) == 0)
    {
        testShader.setTexture(DXTextureManager::getInstance()->getTexture(RSRC_BACKGROUND));
    }
    else
    {
        testShader.setTexture(DXTextureManager::getInstance()->getTexture(RSRC_CHARATER));
    }
    return true;
}

bool Sample::render()
{
    testShader.render();
    return true;
}

bool Sample::release()
{
    testShader.release();
    return true;
}