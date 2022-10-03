#include "UserState_MoveRight.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include "UserState_Jump.hpp"
#include "UserState_Skill_0_1.hpp"
#include "UserState_Falling.hpp"
#include "SkillManager.hpp"

UserState_MoveRight::UserState_MoveRight(Player* _user) : UserState(_user)
{
    initialize();
}

bool UserState_MoveRight::initialize()
{
    textureKeyList.push_back(USER_CHARACTER_WALK_0);
    textureKeyList.push_back(USER_CHARACTER_WALK_1);
    textureKeyList.push_back(USER_CHARACTER_WALK_2);
    textureKeyList.push_back(USER_CHARACTER_WALK_3);

    for (auto it : textureKeyList)
    {
        if (!DXTextureManager::getInstance()->Load(it))
        {
            std::wstring debugStr = L"UserState_MoveLeft::initailize::Failed Texture Load(";
            debugStr += it + L").\n";
            OutputDebugString(debugStr.c_str());
            return false;
        }
    }

    return true;
}

bool UserState_MoveRight::frame()
{
    KeyState KeyState_Right = Input::getInstance()->getKey(VK_RIGHT);
    if ((KeyState_Right == KeyState::Down) || (KeyState_Right == KeyState::Hold))
    {
        float currentTime = Timer::getInstance()->getPlayTime();
        float frameTime = currentTime - beforeTime;
        effectTime += frameTime;
        if (effectTime >= 0.3f)
        {
            effectTime = 0.0f;
            walkState++;
        }
        beforeTime = currentTime;

        if (walkState >= textureKeyList.size())
        {
            walkState = 0;
        }

        user->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[walkState]));

        if (user->currentDirection != Player::Direction::Right)
        {
            user->currentDirection = Player::Direction::Right;

            std::vector<Vertex>* list = user->pShader->getVertexList();

            Vector2f LT = list->at(0).texture;
            Vector2f RT = list->at(1).texture;
            Vector2f LB = list->at(2).texture;
            Vector2f RB = list->at(3).texture;
            
            list->at(0).texture = RT; //{ 1.0f, 0.0f }; // LT
            list->at(1).texture = LT; //{ 0.0f, 0.0f }; // RT
            list->at(2).texture = RB; //{ 1.0f, 1.0f }; // LB
            list->at(3).texture = LB; //{ 0.0f, 1.0f }; // RB
        }
        else
        {
            //user->shape.offset(Vector2f(0.1f, 0.0f));
            user->force.x = 200.0f;
        }

        if (!user->currentMap->CollisionMapObject(user, MapObjectType::Floor))
        {
            user->changeCurrentState<UserState_Falling>();
            return true;
        }
    }
    else
    {
        user->force.x = 0.0f;
        user->accel.x = 0.0f;
        user->velocity.x = 0.0f;
        user->changeCurrentState<UserState_Idle>();
        return true;
    }

    KeyState KeyState_X = Input::getInstance()->getKey('X');
    if ((KeyState_X == KeyState::Down) || (KeyState_X == KeyState::Hold))
    {
        user->changeCurrentState<UserState_Jump>();
        return true;
    }

    // Pick Up
    KeyState KeyState_Z = Input::getInstance()->getKey('Z');
    if ((KeyState_Z == KeyState::Down) || (KeyState_Z == KeyState::Hold))
    {
        //user->changeCurrentState<UserState_Skill_0_1>();
    }

    // Skill 0 Btn
    KeyState KeyState_C = Input::getInstance()->getKey('C');
    if ((KeyState_C == KeyState::Down) || (KeyState_C == KeyState::Hold))
    {
        user->force.x = 0.0f;
        user->accel.x = 0.0f;
        user->velocity.x = 0.0f;
        //user->changeCurrentState<UserState_Skill_0_1>();
        SkillManager::getInstance()->addSkillToJobList(L"Skill_0");
        return true;
    }

    return true;
}

bool UserState_MoveRight::render()
{
    std::wstring strUserState;
    strUserState += L"UserState: ";
    strUserState += L"UserState_MoveRight";
    DXWriter::getInstance()->draw(0, 100, strUserState);

    return true;
}

bool UserState_MoveRight::release()
{
    return true;
}
