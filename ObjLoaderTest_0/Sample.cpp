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
    ObjFile chellObj;
    chellObj.Load(L"../resource/FBX/Portal/Chell/Chell.obj");

    MtlFile chellMtl;
    chellMtl.Load(L"../resource/FBX/Portal/Chell/Chell.mtl");

    MtlFile buttonMtl;
    buttonMtl.Load(L"../resource/FBX/Portal/Button/button.mtl");

    return true;
}

bool Sample::frame()
{
    return true;
}

bool Sample::render()
{
    return true;
}

bool Sample::release()
{
    return true;
}