#include "UserState_Jump.hpp"
#include "Player.hpp"
#include "UserState_Skill_0_1.hpp"
#include "UserState_MoveLeft.hpp"
#include "UserState_MoveRight.hpp"

UserState_Jump::UserState_Jump(Player* _user) : UserState(_user)
{
    initialize();
}

bool UserState_Jump::initialize()
{
    textureKeyList.push_back(USER_CHARACTER_JUMP_0);

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

    user->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[jumpState]));
	user->force.y = -250.0f;

    return true;
}

bool UserState_Jump::frame()
{
	float currentTime = Timer::getInstance()->getPlayTime();
	float frameTime = currentTime - beforeTime;
	user->force.y += 9.81 * frameTime * 10.0;
	beforeTime = currentTime;
	
	// Climb
	KeyState KeyState_Up = Input::getInstance()->getKey(VK_UP);
	if ((KeyState_Up == KeyState::Down) || (KeyState_Up == KeyState::Hold))
	{
		user->force.x = 0.0f;
		user->force.y = 0.0f;
		//user->shape.offset(Vector2f(0.0f, -0.1f));
		return true;
	}

	// Get Down
	KeyState KeyState_Down = Input::getInstance()->getKey(VK_DOWN);
	if ((KeyState_Down == KeyState::Down) || (KeyState_Down == KeyState::Hold))
	{
		user->shape.offset(Vector2f(0.0f, 0.1f));
		//return true;
	}

	// Move to Left
	KeyState KeyState_Left = Input::getInstance()->getKey(VK_LEFT);
	if ((KeyState_Left == KeyState::Down) || (KeyState_Left == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_MoveLeft>();
		return true;
	}

	// Move to Right
	KeyState KeyState_Right = Input::getInstance()->getKey(VK_RIGHT);
	if ((KeyState_Right == KeyState::Down) || (KeyState_Right == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_MoveRight>();
		return true;
	}

	// Jump
	KeyState KeyState_X = Input::getInstance()->getKey('X');
	if ((KeyState_X == KeyState::Down) || (KeyState_X == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_Jump>();
		return true;
	}

	// Skill 0 Btn
	KeyState KeyState_C = Input::getInstance()->getKey('C');
	if ((KeyState_C == KeyState::Down) || (KeyState_C == KeyState::Hold))
	{
		user->changeCurrentState<UserState_Skill_0_1>();
		return true;
	}



    //user->changeCurrentState<UserState_Idle>();
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
