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
    FMODSoundManager::getInstance()->initialize();
    
    if (FMODSoundManager::getInstance()->Load(L"../../resource/sound/abel_leaf.asf"))
    {
        m_pSound = FMODSoundManager::getInstance()->getSound(L"../../resource/sound/abel_leaf.asf");
    }

    FMODSoundManager::getInstance()->LoadDir(L"../../resource/sound/");

    m_pSound->play();
    return true;
}

bool Sample::frame()
{
    FMODSoundManager::getInstance()->frame();
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