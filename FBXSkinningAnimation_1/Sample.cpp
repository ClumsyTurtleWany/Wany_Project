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
    if (FBXLoader::getInstance()->initialize())
    {
        FBXLoader::getInstance()->setResourceDirectory(RESOURCE_DIR);
        pFbxObject = new FBXObject;
        //pFbxObject->initialize();
        //FBXLoader::getInstance()->Load(L"../resource/FBX/MultiCameras.FBX", pFbxObject);
        //FBXLoader::getInstance()->Load(L"../resource/FBX/charMob.FBX", pFbxObject);
        //FBXLoader::getInstance()->Load(L"../resource/FBX/box.FBX", pFbxObject);
        //FBXLoader::getInstance()->Load(L"../resource/FBX/mb2001.FBX", pFbxObject);
        //FBXLoader::getInstance()->Load(L"../resource/FBX/rockBlobSix.FBX", pFbxObject);
        //FBXLoader::getInstance()->Load(L"../resource/FBX/mb10230.FBX", pFbxObject);
        //FBXLoader::getInstance()->Load(L"../resource/FBX/SM_Tree_Var01.FBX", pFbxObject);
        //FBXLoader::getInstance()->Load(L"../resource/FBX/Turret_Deploy1.FBX", pFbxObject); // Object Animation
        //FBXLoader::getInstance()->Load(L"../resource/FBX/Idle.FBX", pFbxObject);
        FBXLoader::getInstance()->Load(L"../resource/FBX/Man.FBX", pFbxObject); // Skinning Animation

        //if (FBXLoader::getInstance()->LoadDir(L"../resource/FBX/"))
        {
            //pFbxObject = FBXLoader::getInstance()->getObject(L"MultiCameras.FBX");
            //pFbxObject = FBXLoader::getInstance()->getObject(L"charMob.FBX");
            //pFbxObject = FBXLoader::getInstance()->getObject(L"box.FBX");
            //pFbxObject = FBXLoader::getInstance()->getObject(L"mb2001.fbx");
            //pFbxObject = FBXLoader::getInstance()->getObject(L"rockBlobSix.FBX");
            //pFbxObject = FBXLoader::getInstance()->getObject(L"mb10230.fbx");
            //pFbxObject = FBXLoader::getInstance()->getObject(L"SM_Tree_Var01.FBX");
            //pFbxObject = FBXLoader::getInstance()->getObject(L"ship.FBX");
            //pFbxObject = FBXLoader::getInstance()->getObject(L"Turret_Deploy1.FBX");
        }

        //pFbxObject->rotationYawPitchRoll(90.0f, 90.0f, 0);
    }

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
            //pBoxObject->createShader(ShaderType::Axis3D);
            pBoxObject->setTexture(pTexture);
            pBoxObject->initialize();
            pBoxObject->translation(-2.0f, 0.0f, -2.0f);

            /*pBoxObject->pShader->updateVertexList(&vertexList[0]);
            std::vector<DWORD> indexList;
            for (DWORD i = 0; i < vertexList[0].size(); i++)
            {
                indexList.push_back(i);
            }
            pBoxObject->pShader->updateIndexList(&indexList);*/
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
    renderCamera->CreateMatrix_View(Vector3f(0.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    renderCamera->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, static_cast<float>(g_pWindow->getClientWidth()) / static_cast<float>(g_pWindow->getClientHeight()));
    renderCamera->initialize();

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

    textureRenderTarget.setDevice(m_pd3dDevice, m_pImmediateContext);
    textureRenderTarget.create(1024, 768);

    return true;
}

bool Sample::frame()
{
    FBXLoader::getInstance()->frame();

    float dt = Timer::getInstance()->getDeltaTime();
    float gameTime = Timer::getInstance()->gameTime;
    renderCamera->frame();
    for (int idx = 0; idx < 4; idx++)
    {
        ViewPortCamera[idx]->frame();
    }

    pObject->frame(dt);
    pObject->testTime = gameTime;
    //pObject->translation(cos(gameTime) * 10.0f * dt, cos(gameTime) * 10.0f * dt, cos(gameTime) * 10.0f * dt);

    pBoxObject->testTime = gameTime;
    pBoxObject->rotationYawPitchRoll(gameTime * 2.0f, 0.0f, 0.0f);
    Matrix4x4 matRotationY = Make3DMatrix_RotationY(dt);
    pBoxObject->data.matWorld = pBoxObject->data.matWorld * matRotationY;
    pBoxObject->frame(dt);

    pWorldMap->frame(dt);


    pFbxObject->frame(dt);

    return true;
}

bool Sample::render()
{
    FBXLoader::getInstance()->render();

    KeyState KeyState_F4 = Input::getInstance()->getKey(VK_F4);
    if (KeyState_F4 == KeyState::Hold)
    {
        m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSWireFrame);
    }

    //if (textureRenderTarget.begin())
    {
        // 메인 뷰 포트 렌더링

        Matrix4x4 matView = renderCamera->getMatrix_View();
        Matrix4x4 matProj = renderCamera->getMatrix_Projection();

        //if (renderCamera->frustum.classifyPoint(pBoxObject->curPos))
        //{
        //    pBoxObject->setMatrix(nullptr, &matView, &matProj);
        //    pBoxObject->render();
        //}
        //
        //if (renderCamera->frustum.classifyPoint(pObject->curPos))
        //{
        //    pObject->setMatrix(nullptr, &matView, &matProj);
        //    pObject->render();
        //}

        //if (renderCamera->frustum.classifyPoint(pWorldMap->curPos))
        //{
        //    pWorldMap->setMatrix(nullptr, &matView, &matProj);
        //    pWorldMap->render();
        //}

        pFbxObject->setMatrix(nullptr, &matView, &matProj);
        pFbxObject->render();

        //// 서브 뷰 포트 렌더링
        //// 1. 메인 뷰 포트 저장.
        //D3D11_VIEWPORT vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
        //UINT nViewPorts = 1;
        //m_pImmediateContext->RSGetViewports(&nViewPorts, vpOld);

        //// 2. Depth Stencil View Clear. 
        //// Depth Stencil View를 클리어 해 주지 않으면 위의 메인 뷰 포트에서 그려진 오브젝트로 인해 아래의 뷰포트들이 출력 안될 수도 있다.
        //m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); // Depth는 1.0f, Stencil은 0으로 클리어.

        //// 3. 서브 뷰포트 렌더링
        //for (int idx = 0; idx < 4; idx++)
        //{
        //    m_pImmediateContext->RSSetViewports(1, &ViewPort[idx]);


        //    KeyState KeyState_F4 = Input::getInstance()->getKey(VK_F4);
        //    if (KeyState_F4 == KeyState::Hold)
        //    {
        //        m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSWireFrame);
        //    }

        //    Matrix4x4 matView_idx = ViewPortCamera[idx]->getMatrix_View();
        //    Matrix4x4 matProj_idx = ViewPortCamera[idx]->getMatrix_Projection();

        //    pBoxObject->setMatrix(nullptr, &matView_idx, &matProj_idx);
        //    pBoxObject->render();

        //    pObject->setMatrix(nullptr, &matView_idx, &matProj_idx);
        //    pObject->render();

        //    //pWorldMap->setMatrix(nullptr, &matView_idx, &matProj_idx);
        //    //pWorldMap->render();
        //}

        //// 원래 뷰포트로 다시 세팅.
        //m_pImmediateContext->RSSetViewports(1, &vpOld[0]);


        m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); // Depth는 1.0f, Stencil은 0으로 클리어.
        renderCamera->render();

        //textureRenderTarget.end();
    }

    //textureRenderTarget.render();
    return true;
}

bool Sample::release()
{
    FBXLoader::getInstance()->release();

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

    textureRenderTarget.release();
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
