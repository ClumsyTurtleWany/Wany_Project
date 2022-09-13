#include "UserState_Skill_0.hpp"
#include "Player.hpp"

UserState_Skill_0::UserState_Skill_0(Player* _user) : UserState(_user)
{
    initialize();
}

bool UserState_Skill_0::initialize()
{
    skill = new object2D<float>(Rect2f(200, 200, 504, 332));
    skill->createShader(ShaderType::Texture);

    // 1
    textureKeyList.push_back(USER_STATE_SKILL_0_0_0);
    textureKeyList.push_back(USER_STATE_SKILL_0_0_1);
    textureKeyList.push_back(USER_STATE_SKILL_0_0_2);
    textureKeyList.push_back(USER_STATE_SKILL_0_0_3);
    textureKeyList.push_back(USER_STATE_SKILL_0_0_4);
    textureKeyList.push_back(USER_STATE_SKILL_0_0_5);
    textureKeyList.push_back(USER_STATE_SKILL_0_0_6);
    textureKeyList.push_back(USER_STATE_SKILL_0_1_0);
    textureKeyList.push_back(USER_STATE_SKILL_0_1_1);
    textureKeyList.push_back(USER_STATE_SKILL_0_1_2);
    textureKeyList.push_back(USER_STATE_SKILL_0_1_3);
    textureKeyList.push_back(USER_STATE_SKILL_0_1_4);
    textureKeyList.push_back(USER_STATE_SKILL_0_1_5);
    textureKeyList.push_back(USER_STATE_SKILL_0_1_6);
    textureKeyList.push_back(USER_STATE_SKILL_0_2_0);
    textureKeyList.push_back(USER_STATE_SKILL_0_2_1);
    textureKeyList.push_back(USER_STATE_SKILL_0_2_2);
    textureKeyList.push_back(USER_STATE_SKILL_0_2_3);
    textureKeyList.push_back(USER_STATE_SKILL_0_2_4);
    textureKeyList.push_back(USER_STATE_SKILL_0_2_5);
    textureKeyList.push_back(USER_STATE_SKILL_0_2_6);

    for (auto it : textureKeyList)
    {
        if (!DXTextureManager::getInstance()->Load(it))
        {
            std::wstring debugStr = L"Skill::initailize::Failed Texture Load(";
            debugStr += it + L").\n";
            OutputDebugString(debugStr.c_str());
            return false;
        }
    }

    skill->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[skillState]));

    beforeFrameTime = static_cast<float>(timeGetTime());
    return true;
}

bool UserState_Skill_0::frame()
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
        std::wstring strTime = L"Skill[" + std::to_wstring(skillState) +  L"] Time: " + std::to_wstring(frameTime) + L"\n";
        OutputDebugString(strTime.c_str());

        if (skillState < textureKeyList.size() - 1)
        {
            skillState++;
        }
        else
        {
            skillState = 0;
            skill->release();
            delete skill;
            skill = nullptr;
            user->changeCurrentState<UserState_Idle>();

            return true;
        }

        FPS = 0;
        //frameTime = 0.0f;

        skill->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[skillState]));
    }
    return true;
}

bool UserState_Skill_0::render()
{
    skill->render();
    return true;
}

bool UserState_Skill_0::release()
{
    return true;
}
