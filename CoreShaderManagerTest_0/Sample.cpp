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
    DXShaderManager<testKey>::getInstance()->setDevice(m_pd3dDevice, m_pImmediateContext);

    testShader.setDevice(m_pd3dDevice, m_pImmediateContext);
    testShader.setShaderFile(L"../include/core/HLSL/ShapeShader.txt");

    testTexture.setDevice(m_pd3dDevice, m_pImmediateContext);
    testTexture.Load(L"../../resource/KGCABK.bmp");

    testShader.setTexture(&testTexture);

    bool rst = testShader.initialize();

    
    return true;
}

bool Sample::frame()
{
    testShader.frame();
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