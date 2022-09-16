#include "UserState_Jump.hpp"
#include "Player.hpp"

UserState_Jump::UserState_Jump(Player* _user) : UserState(_user)
{
    initialize();
}

bool UserState_Jump::initialize()
{
    
    return true;
}

bool UserState_Jump::frame()
{
    user->changeCurrentState<UserState_Idle>();
    return true;
}

bool UserState_Jump::render()
{
    return true;
}

bool UserState_Jump::release()
{
    return true;
}
