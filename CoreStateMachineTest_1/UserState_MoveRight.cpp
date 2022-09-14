#include "UserState_MoveRight.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include "UserState_Jump.hpp"
#include "UserState_Skill_0.hpp"

UserState_MoveRight::UserState_MoveRight(Player* _user) : UserState(_user)
{
    initialize();
}

bool UserState_MoveRight::initialize()
{
    return true;
}

bool UserState_MoveRight::frame()
{
    KeyState KeyState_Right = Input::getInstance()->getKey(VK_RIGHT);
    if ((KeyState_Right == KeyState::Down) || (KeyState_Right == KeyState::Hold))
    {
        if (user->currentDirection != Player::Direction::Right)
        {
            user->currentDirection = Player::Direction::Right;

            std::vector<Vertex>* list = user->pObj->pShader->getVertexList();
            list->at(0).texture = { 1.0f, 0.0f }; // LT
            list->at(1).texture = { 0.0f, 0.0f }; // RT
            list->at(2).texture = { 1.0f, 1.0f }; // LB
            list->at(3).texture = { 0.0f, 1.0f }; // RB
        }
        else
        {
            user->pObj->shape.offset(Vector2f(1.0f, 0.0f));
        }
    }
    else
    {
        user->changeCurrentState<UserState_Idle>();
        return true;
    }

    KeyState KeyState_X = Input::getInstance()->getKey('X');
    if ((KeyState_X == KeyState::Down) || (KeyState_X == KeyState::Hold))
    {
        user->changeCurrentState<UserState_Jump>();
    }

    // Pick Up
    KeyState KeyState_Z = Input::getInstance()->getKey('Z');
    if ((KeyState_Z == KeyState::Down) || (KeyState_Z == KeyState::Hold))
    {
        //user->changeCurrentState<UserState_Skill_0>();
    }

    // Skill 0 Btn
    KeyState KeyState_C = Input::getInstance()->getKey('C');
    if ((KeyState_C == KeyState::Down) || (KeyState_C == KeyState::Hold))
    {
        user->changeCurrentState<UserState_Skill_0>();
        return true;
    }

    return true;
}

bool UserState_MoveRight::render()
{
    return true;
}

bool UserState_MoveRight::release()
{
    return true;
}
