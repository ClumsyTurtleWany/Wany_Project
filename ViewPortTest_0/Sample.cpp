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
    float height = g_pWindow->getClientHeight() / 4.0f;
    float width = height;

    for (int idx = 0; idx < 4; idx++)
    {
        ViewPort[idx].TopLeftX = 0;
        ViewPort[idx].TopLeftY = idx * height;
        ViewPort[idx].Width = width;
        ViewPort[idx].Height = height;
        ViewPort[idx].MinDepth = 0;
        ViewPort[idx].MaxDepth = 1;
    }
    m_pImmediateContext->RSSetViewports(4, ViewPort);

    if (DXTextureManager::getInstance()->Load(CHARACTER_DIR))
    {
        DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(CHARACTER_DIR);
        if (pTexture != nullptr)
        {
            float width = pTexture->getWidth();
            float height = pTexture->getHeight();
            float x = (g_pWindow->getClientWidth() - width) / 2.0f;
            float y = (g_pWindow->getClientHeight() - height) / 2.0f;

            pObject = new Plane3D;
            pObject->createShader(ShaderType::Object3D);
            pObject->setTexture(pTexture);
            pObject->initialize();

            pBoxObject = new Cube3D;
            pBoxObject->createShader(ShaderType::Object3D);
            pBoxObject->setTexture(pTexture);
            pBoxObject->initialize();
            pBoxObject->translation(-2.0f, 0.0f, -2.0f);
        }
    }    

    if (DXTextureManager::getInstance()->Load(MAP_DIR))
    {
        DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(MAP_DIR);
        if (pTexture != nullptr)
        {
            float width = pTexture->getWidth();
            float height = pTexture->getHeight();
            float x = (g_pWindow->getClientWidth() - width) / 2.0f;
            float y = (g_pWindow->getClientHeight() - height) / 2.0f;

            pWorldMap = new Map3D;
            pWorldMap->createShader(ShaderType::Object3D);
            pWorldMap->setTexture(pTexture);
            pWorldMap->build(513, 513);
            pWorldMap->initialize();
        }
    }   

    renderCamera = new Camera(ProjectionType::Perspective);
    renderCamera->CreateMatrix_View(Vector3f(0.0f, 10.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    renderCamera->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, static_cast<float>(g_pWindow->getClientWidth()) / static_cast<float>(g_pWindow->getClientHeight()));

    return true;
}

bool Sample::frame()
{
    float dt = Timer::getInstance()->getDeltaTime();
    float gameTime = Timer::getInstance()->gameTime;
    renderCamera->frame();
    pObject->frame(dt);
    pObject->testTime = gameTime;
    pObject->translation(cos(gameTime) * 10.0f * dt, cos(gameTime) * 10.0f * dt, cos(gameTime) * 10.0f * dt);

    pBoxObject->frame(dt);
    pBoxObject->testTime = gameTime;
    
    Matrix4x4 matRotationY = Make3DMatrix_RotationY(dt);
    pBoxObject->data.matWorld = pBoxObject->data.matWorld * matRotationY;
    pWorldMap->frame(dt);
   
    return true;
}

bool Sample::render()
{
    KeyState KeyState_F4 = Input::getInstance()->getKey(VK_F4);
    if (KeyState_F4 == KeyState::Hold)
    {
        m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSWireFrame);
    }

    Matrix4x4 matView = renderCamera->getMatrix_View();
    Matrix4x4 matProj = renderCamera->getMatrix_Projection();

    pBoxObject->setMatrix(nullptr, &matView, &matProj);
    pBoxObject->render();

    pObject->setMatrix(nullptr, &matView, &matProj);
    pObject->render();

    pWorldMap->setMatrix(nullptr, &matView, &matProj);
    pWorldMap->render();

    // 뷰포트 저장
    D3D11_VIEWPORT vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
    UINT nViewPorts = 1;
    m_pImmediateContext->RSGetViewports(&nViewPorts, vpOld);

    // 뷰포트 렌더링
    for (int idx = 0; idx < 4; idx++)
    {
        m_pImmediateContext->RSSetViewports(1, &ViewPort[idx]);

        KeyState KeyState_F4 = Input::getInstance()->getKey(VK_F4);
        if (KeyState_F4 == KeyState::Hold)
        {
            m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSWireFrame);
        }

        Matrix4x4 matView = renderCamera->getMatrix_View();
        Matrix4x4 matProj = renderCamera->getMatrix_Projection();

        pBoxObject->setMatrix(nullptr, &matView, &matProj);
        pBoxObject->render();

        pObject->setMatrix(nullptr, &matView, &matProj);
        pObject->render();

        pWorldMap->setMatrix(nullptr, &matView, &matProj);
        pWorldMap->render();
    }

    // 원래 뷰포트로 다시 세팅.
    m_pImmediateContext->RSSetViewports(1, &vpOld[0]);
        
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

    if (pBoxObject != nullptr)
    {
        pBoxObject->release();
        delete pBoxObject;
        pBoxObject = nullptr;
    }

    if (pWorldMap != nullptr)
    {
        pWorldMap->release();
        delete pWorldMap;
        pWorldMap = nullptr;
    }
    return true;
}