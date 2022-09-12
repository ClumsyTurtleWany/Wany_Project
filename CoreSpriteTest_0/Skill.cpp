#include "Skill.hpp"

bool Skill::initialize()
{
    skill = new object2D<float>(Rect2f(200, 200, 504, 332));
    skill->createShader(ShaderType::Texture);

    // 1
    if (!DXTextureManager::getInstance()->Load(SKILL_0_0))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_0_1))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_0_2))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_0_3))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_0_4))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_0_5))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_0_6))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    // 2
    if (!DXTextureManager::getInstance()->Load(SKILL_1_0))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_1_1))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_1_2))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_1_3))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_1_4))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_1_5))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_1_6))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    // 3
    if (!DXTextureManager::getInstance()->Load(SKILL_2_0))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_2_1))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_2_2))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_2_3))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_2_4))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_2_5))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    if (!DXTextureManager::getInstance()->Load(SKILL_2_6))
    {
        OutputDebugString(L"Skill::initailize::Failed Texture Load.");
        return false;
    }

    beforeFrameTime = static_cast<float>(timeGetTime());
	return true;
}

bool Skill::frame()
{
    float currentFrameTime = static_cast<float>(timeGetTime());
    secondPerFrame = (currentFrameTime - beforeFrameTime) / 1000.0f;
    frameTime += secondPerFrame;
    beforeFrameTime = currentFrameTime;
    FPS++;
   
    std::wstring strTime = L"frame Time: " + std::to_wstring(secondPerFrame) + L"\n";
    OutputDebugString(strTime.c_str());
   
    if (FPS >= 45)
    {
        std::wstring strTime = L"Skill Time: " + std::to_wstring(frameTime) + L"\n";
        OutputDebugString(strTime.c_str());

        if (skillState == 21)
        {
            skillState = 0;
        }
        else
        {
            skillState++;
        }

        FPS = 0;
        //frameTime = 0.0f;


        switch (skillState)
        {
            // 1
        case 0:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_0_0));
            break;
        case 1:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_0_1));
            break;
        case 2:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_0_2));
            break;
        case 3:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_0_3));
            break;
        case 4:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_0_4));
            break;
        case 5:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_0_5));
            break;
        case 6:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_0_6));
            break;
            // 2
        case 7:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_1_0));
            break;
        case 8:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_1_1));
            break;
        case 9:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_1_2));
            break;
        case 10:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_1_3));
            break;
        case 11:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_1_4));
            break;
        case 12:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_1_5));
            break;
        case 13:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_1_6));
            break;
            // 3
        case 14:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_2_0));
            break;
        case 15:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_2_1));
            break;
        case 16:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_2_2));
            break;
        case 17:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_2_3));
            break;
        case 18:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_2_4));
            break;
        case 19:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_2_5));
            break;
        case 20:
            skill->setTexture(DXTextureManager::getInstance()->getTexture(SKILL_2_6));
            break;
        }

    }
	return true;
}

bool Skill::render()
{
    skill->render();
	return true;
}

bool Skill::release()
{
	return true;
}
