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

    renderCamera = new DebugCamera(ProjectionType::Perspective);
    renderCamera->CreateMatrix_View(Vector3f(0.0f, 10.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    renderCamera->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, static_cast<float>(g_pWindow->getClientWidth()) / static_cast<float>(g_pWindow->getClientHeight()));

    // Front View
    ViewPortCamera[0] = new Camera(ProjectionType::Perspective);
    ViewPortCamera[0]->CreateMatrix_View(Vector3f(0.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    ViewPortCamera[0]->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, (ViewPort[0].Width / ViewPort[0].Height));

    // Top View
    ViewPortCamera[1] = new Camera(ProjectionType::Perspective);
    ViewPortCamera[1]->CreateMatrix_View(Vector3f(0.0f, 10.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));
    ViewPortCamera[1]->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, (ViewPort[1].Width / ViewPort[1].Height));

    // Right View
    ViewPortCamera[2] = new Camera(ProjectionType::Perspective);
    ViewPortCamera[2]->CreateMatrix_View(Vector3f(10.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    ViewPortCamera[2]->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, (ViewPort[2].Width / ViewPort[2].Height));

    // Bottom View
    ViewPortCamera[3] = new Camera(ProjectionType::Perspective);
    ViewPortCamera[3]->CreateMatrix_View(Vector3f(0.0f, -10.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, -1.0f));
    ViewPortCamera[3]->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, (ViewPort[3].Width / ViewPort[3].Height));

    return true;
}

bool Sample::frame()
{
    float dt = Timer::getInstance()->getDeltaTime();
    float gameTime = Timer::getInstance()->gameTime;
    renderCamera->frame();
    for (int idx = 0; idx < 4; idx++)
    {
        ViewPortCamera[idx]->frame();
    }

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
    // ���� �� ��Ʈ ������
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

    // ���� �� ��Ʈ ������
    // 1. ���� �� ��Ʈ ����.
    D3D11_VIEWPORT vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
    UINT nViewPorts = 1;
    m_pImmediateContext->RSGetViewports(&nViewPorts, vpOld);

    // 2. Depth Stencil View Clear. 
    // Depth Stencil View�� Ŭ���� �� ���� ������ ���� ���� �� ��Ʈ���� �׷��� ������Ʈ�� ���� �Ʒ��� ����Ʈ���� ��� �ȵ� ���� �ִ�.
    m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); // Depth�� 1.0f, Stencil�� 0���� Ŭ����.

    // 3. ���� ����Ʈ ������
    for (int idx = 0; idx < 4; idx++)
    {
        m_pImmediateContext->RSSetViewports(1, &ViewPort[idx]);


        KeyState KeyState_F4 = Input::getInstance()->getKey(VK_F4);
        if (KeyState_F4 == KeyState::Hold)
        {
            m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSWireFrame);
        }

        Matrix4x4 matView_idx = ViewPortCamera[idx]->getMatrix_View();
        Matrix4x4 matProj_idx = ViewPortCamera[idx]->getMatrix_Projection();

        pBoxObject->setMatrix(nullptr, &matView_idx, &matProj_idx);
        pBoxObject->render();

        pObject->setMatrix(nullptr, &matView_idx, &matProj_idx);
        pObject->render();

        pWorldMap->setMatrix(nullptr, &matView_idx, &matProj_idx);
        pWorldMap->render();
    }

    // ���� ����Ʈ�� �ٽ� ����.
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

bool Sample::resize()
{
    DXDevice::resize();

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

    return true;
}
