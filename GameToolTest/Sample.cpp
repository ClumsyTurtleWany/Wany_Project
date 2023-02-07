#include "pch.h"
#include "Sample.h"

#include <crtdbg.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#include "DXMath.hpp"

bool Sample::initialize()
{
    pMainAxis = new Axis3D();
    pMainAxis->setAxisSize(100.0f, 100.0f, 100.0f);
    pMainAxis->createShader(ShaderType::Axis3D);
    pMainAxis->initialize();
    
    renderCamera = new DebugCamera(ProjectionType::Perspective);
    renderCamera->CreateMatrix_View(Vector3f(0.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    renderCamera->CreateMatrix_Proj(1.0f, 10000.0f, PI * 0.25f, static_cast<float>(g_pWindow->getClientWidth()) / static_cast<float>(g_pWindow->getClientHeight()));
    renderCamera->initialize();

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


    return true;
}

bool Sample::frame()
{
    float dt = Timer::getInstance()->getDeltaTime();
    float gameTime = Timer::getInstance()->gameTime;
    
    pMainAxis->frame(dt);
    renderCamera->frame();

   
    //pObject->moveTo()
    pObject->frame(dt);
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
    
    Matrix4x4 matWorld;
    matWorld.Identity();
    Matrix4x4 matView = renderCamera->getMatrix_View();
    Matrix4x4 matProj = renderCamera->getMatrix_Projection();
    
    pMainAxis->setMatrix(&matWorld, &matView, &matProj);
    pMainAxis->render();
    
    renderCamera->render();


    pWorldMap->setMatrix(&matWorld, &matView, &matProj);
    pWorldMap->render();

    POINT ptMouse = Input::getInstance()->m_ptPos;
    float projRayDir_x = ((2.0f * ptMouse.x) / (clientRect.right - clientRect.left) - 1);
    float projRayDir_y = -((2.0f * ptMouse.y) / (clientRect.bottom - clientRect.top) - 1);
    float projRayDir_z = 1.0f;

    float viewRayDir_x = projRayDir_x / matProj._11;
    float viewRayDir_y = projRayDir_y / matProj._22;
    float viewRayDir_z = 1.0f;

    Matrix4x4 matWorldView = matWorld * matView;
    Matrix4x4 inversedView = MakeInversedMatrix(matWorldView);
    float PickRayDir_x = viewRayDir_x * inversedView._11 + viewRayDir_y * inversedView._21 + viewRayDir_z * inversedView._31;
    float PickRayDir_y = viewRayDir_x * inversedView._12 + viewRayDir_y * inversedView._22 + viewRayDir_z * inversedView._32;
    float PickRayDir_z = viewRayDir_x * inversedView._13 + viewRayDir_y * inversedView._23 + viewRayDir_z * inversedView._33;
    Vector3f normalizedRayVec(PickRayDir_x, PickRayDir_y, PickRayDir_z);
    normalizedRayVec = normalizedRayVec.normalized();

    Vector3f RayOrigin(inversedView._41, inversedView._42, inversedView._43);
    
    pObject->setMatrix(&matWorld, &matView, &matProj);
    pObject->translation(normalizedRayVec.x * 1.0f, normalizedRayVec.y * 1.0f, normalizedRayVec.z * 1.0f);
    pObject->render();

    return true;
}

bool Sample::release()
{
    if (pMainAxis != nullptr)
    {
        pMainAxis->release();
        delete pMainAxis;
        pMainAxis = nullptr;
    }
    
    if (renderCamera != nullptr)
    {
        renderCamera->release();
        delete renderCamera;
        renderCamera = nullptr;
    }

    return true;
}

bool Sample::resize()
{
    GetClientRect(hWnd, &clientRect);
    DXDevice::resize();

    float height = g_pWindow->getClientHeight() / 4.0f;
    float width = height;

    /*for (int idx = 0; idx < 4; idx++)
    {
        ViewPort[idx].TopLeftX = 0;
        ViewPort[idx].TopLeftY = idx * height;
        ViewPort[idx].Width = width;
        ViewPort[idx].Height = height;
        ViewPort[idx].MinDepth = 0;
        ViewPort[idx].MaxDepth = 1;
    }*/

    return true;
}
