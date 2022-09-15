#include "UserState_Skill_0_3.hpp"
#include "Player.hpp"

UserState_Skill_0_3::UserState_Skill_0_3(Player* _user) : UserState(_user)
{
    initialize();
}

bool UserState_Skill_0_3::initialize()
{
    float x = 0.0f;
    float y = 0.0f;
    float width = 504;
    float height = 332;

    float hitboxOffset_x = 10.0f;
    float hitboxOffset_y = 10.0f;
    float hitbox_x = 0.0f;
    float hitbox_y = 0.0f;
    float hitbox_width = 0.0f;
    float hitbox_height = 0.0f;
    if (user->currentDirection == Player::Direction::Left)
    {
        x = user->pObj->shape.cx() - width;
        y = user->pObj->shape.cy() - height;
        
        hitbox_x = x + hitboxOffset_x;
        hitbox_y = y + hitboxOffset_y;
        hitbox_width = width - (hitboxOffset_x * 2.0f);
        hitbox_height = height - (hitboxOffset_y * 2.0f);
    }
    else
    {
        x = user->pObj->shape.cx();
        y = user->pObj->shape.cy() - height;

        hitbox_x = x + hitboxOffset_x;
        hitbox_y = y + hitboxOffset_y;
        hitbox_width = width - (hitboxOffset_x * 2.0f);
        hitbox_height = height - (hitboxOffset_y * 2.0f);
    }
    skill = new object2D<float>(Rect2f(x, y, 504, 332));
    skill->createShader(ShaderType::Texture);

    skill->hitbox = Rect2f(hitbox_x, hitbox_y, hitbox_width, hitbox_height);

    // 1
    /*textureKeyList.push_back(USER_STATE_SKILL_0_0_0);
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
    textureKeyList.push_back(USER_STATE_SKILL_0_1_6);*/
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

    std::vector<Vertex>* UserVertexList = user->pObj->pShader->getVertexList();
    std::vector<Vertex>* skillVertexList = skill->pShader->getVertexList();
    skillVertexList->at(0).texture = UserVertexList->at(0).texture;
    skillVertexList->at(1).texture = UserVertexList->at(1).texture;
    skillVertexList->at(2).texture = UserVertexList->at(2).texture;
    skillVertexList->at(3).texture = UserVertexList->at(3).texture;

    beforeFrameTime = static_cast<float>(timeGetTime());
    return true;
}

bool UserState_Skill_0_3::frame()
{
    float currentFrameTime = static_cast<float>(timeGetTime());
    secondPerFrame = (currentFrameTime - beforeFrameTime) / 1000.0f;
    frameTime += secondPerFrame;
    beforeFrameTime = currentFrameTime;
    FPS++;

    std::wstring strTime = L"frame Time: " + std::to_wstring(secondPerFrame) + L"\n";
    OutputDebugString(strTime.c_str());

    if (skillState == 0)
    {
        std::vector<objectBase*> collisionList;
        std::vector<Rect2f> collisionRectList;
        user->currentMap->Collision(skill, &collisionList, &collisionRectList);
        for (auto it : collisionRectList)
        {
            DrawBorder(it, BORDER_COLOR_BLUE);
        }

        int a = 0;
    }

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

bool UserState_Skill_0_3::render()
{
    skill->render();
    DrawBorder(skill->hitbox, BORDER_COLOR_GREEN);
    return true;
}

bool UserState_Skill_0_3::release()
{
    return true;
}
