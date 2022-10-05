#include "MapleStory.h"
#include "Scene_Intro.hpp"
// 2022-09-06

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    MapleStory sampleWindow;
    //sampleWindow.createWindow(hInstance, L"TestName", 1024, 768);
    sampleWindow.createWindow(hInstance, L"TestName", 1366, 768);
    sampleWindow.run();

    return 1;
}

bool MapleStory::initialize()
{
    if (!FMODSoundManager::getInstance()->LoadDir(SOUND_DIRECTORY))
    {
        std::wstring debugStr = L"MapleStory::FMODSoundManager::Failed Load(";
        debugStr += SOUND_DIRECTORY;
        debugStr += L").\n";
        OutputDebugString(debugStr.c_str());
    }

    //if (!SkillManager::getInstance()->Load(SKILL_DIRECTORY))
    //{
    //    std::wstring debugStr = L"MapleStory::SkillManager::Failed Load(";
    //    debugStr += SKILL_DIRECTORY;
    //    debugStr += L").\n";
    //    OutputDebugString(debugStr.c_str());
    //}

    if (!EffectManager::getInstance()->Load(EFFECT_DIRECTORY))
    {
        std::wstring debugStr = L"MapleStory::EffectManager::Failed Load(";
        debugStr += EFFECT_DIRECTORY;
        debugStr += L").\n";
        OutputDebugString(debugStr.c_str());
    }

    if (!NPCManager::getInstance()->Load(NPC_DIRECTORY))
    {
        std::wstring debugStr = L"MapleStory::NPCManager::Failed Load(";
        debugStr += NPC_DIRECTORY;
        debugStr += L").\n";
        OutputDebugString(debugStr.c_str());
    }

    if (!UIManager::getInstance()->Load(UI_DIRECTORY))
    {
        std::wstring debugStr = L"MapleStory::UIManager::Failed Load(";
        debugStr += UI_DIRECTORY;
        debugStr += L").\n";
        OutputDebugString(debugStr.c_str());
    }

    changeCurrentScene<Scene_Intro>();

    return true;
}

bool MapleStory::frame()
{
    KeyState KeyState_F4 = Input::getInstance()->getKey(VK_F4);
    if ((KeyState_F4 == KeyState::Down) || (KeyState_F4 == KeyState::Hold))
    {
        DXShaderBorderManager::getInstance()->setVisible(true);
    }
    else
    {
        DXShaderBorderManager::getInstance()->setVisible(false);
    }

    currentScene->frame();
    return true;
}

bool MapleStory::render()
{
    currentScene->render();
    return true;
}

bool MapleStory::release()
{
    currentScene->release();
    return true;
}