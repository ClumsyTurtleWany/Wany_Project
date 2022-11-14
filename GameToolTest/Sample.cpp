#include "pch.h"
#include "Sample.h"

#include <crtdbg.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

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

    return true;
}

bool Sample::frame()
{
    float dt = Timer::getInstance()->getDeltaTime();
    float gameTime = Timer::getInstance()->gameTime;
    
    pMainAxis->frame(dt);
    renderCamera->frame();
    
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
