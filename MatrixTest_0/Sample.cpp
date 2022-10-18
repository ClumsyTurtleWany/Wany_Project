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

            //pBoxObject = new BoxObject;
            //pBoxObject->createShader(ShaderType::Object3D);
            //pBoxObject->initVertex();
            //pBoxObject->setTexture(pTexture);
            
        }
    }    

    renderCamera = new Camera(ProjectionType::Perspective);
    renderCamera->CreateMatrix_View(Vector3f(0.0f, 1.0f, -27.79f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    renderCamera->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, static_cast<float>(g_pWindow->getClientWidth()) / static_cast<float>(g_pWindow->getClientHeight()));


    return true;
}

bool Sample::frame()
{
    float dt = Timer::getInstance()->getDeltaTime();
    renderCamera->frame();
    pObject->frame(dt);
    //pBoxObject->frame(dt);
   
    return true;
}

bool Sample::render()
{
    KeyState KeyState_F4 = Input::getInstance()->getKey(VK_F4);
    if (KeyState_F4 == KeyState::Hold)
    {
        m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSWireFrame);
    }

    Matrix4x4 identity;
    identity.Identity();
   /* pBoxObject->setMatrix(identity, renderCamera->getMatrix_View(), renderCamera->getMatrix_Projection());
    pBoxObject->render();*/

   // pObject->setMatrix(identity, renderCamera->getMatrix_View(), renderCamera->getMatrix_Projection());
    pObject->setMatrix(identity, renderCamera->getMatrix_View(), renderCamera->getMatrix_Projection());
    //pObject->setMatrix(identity, identity, identity);
    pObject->render();
    return true;
}

bool Sample::release()
{
    if (pObject != nullptr)
    {
        pObject->release();
        delete pObject;
        pObject = nullptr;
    }

    /*if (pBoxObject != nullptr)
    {
        pBoxObject->release();
        delete pBoxObject;
        pBoxObject = nullptr;
    }*/
    return true;
}