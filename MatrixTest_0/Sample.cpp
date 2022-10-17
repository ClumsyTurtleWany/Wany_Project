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
    
    if (DXTextureManager::getInstance()->Load(CHARACTER_DIR))
    {
        DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(CHARACTER_DIR);
        if (pTexture != nullptr)
        {
            float width = pTexture->getWidth();
            float height = pTexture->getHeight();
            float x = (g_pWindow->getClientWidth() - width) / 2.0f;
            float y = (g_pWindow->getClientHeight() - height) / 2.0f;

            pObject = new NewObject;
            pObject->shape = Rect2f(x, y, width, height);
            pObject->createShader(ShaderType::Object3D);
            pObject->setTexture(pTexture);
        }
    }    

    return true;
}

bool Sample::frame()
{
    float dt = Timer::getInstance()->getDeltaTime();
    pObject->frame(dt);
    return true;
}

bool Sample::render()
{
    pObject->render();
    return true;
}

bool Sample::release()
{
    pObject->release();
    delete pObject;
    pObject = nullptr;
    return true;
}