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
    DXShaderManager::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);

    if (!DXTextureManager::getInstance()->Load(RSRC_BACKGROUND))
    {
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(RSRC_CHARATER))
    {
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(RSRC_CHARATER_MASK))
    {
        return false;
    }

    if (!DXShaderManager::getInstance()->Load(0, ShaderType::Normal))
    {
        return false;
    }

    if (!DXShaderManager::getInstance()->Load(1, ShaderType::Mask))
    {

    }

    Background = DXShaderManager::getInstance()->getShader(0);
    Background->setTexture(DXTextureManager::getInstance()->getTexture(RSRC_BACKGROUND));
       
    user = DXShaderManager::getInstance()->getShader(1);
    user->setTexture(DXTextureManager::getInstance()->getTexture(RSRC_CHARATER));
    user->setTextureMask(DXTextureManager::getInstance()->getTexture(RSRC_CHARATER_MASK));
    return true;
}

bool Sample::frame()
{
    Background->frame();
    user->frame();
    return true;
}

bool Sample::render()
{
    Background->render();
    user->render();
    return true;
}

bool Sample::release()
{
    DXShaderManager::getInstance()->release();
    return true;
}