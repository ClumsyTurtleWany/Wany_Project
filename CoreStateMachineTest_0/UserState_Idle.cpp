#include "UserState_Idle.hpp"
#include "UserState_Skill_0.hpp"
#include "Player.hpp"

UserState_Idle::UserState_Idle(Player* _user) : UserState(_user)
{
}

bool UserState_Idle::initialize()
{
	return true;
}

bool UserState_Idle::frame()
{
	KeyState KeyState_Up = Input::getInstance()->getKey(VK_UP);
	if ((KeyState_Up == KeyState::Down) || (KeyState_Up == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_Skill_0>();
		return true;
	}

	KeyState KeyState_Down = Input::getInstance()->getKey(VK_DOWN);
	if ((KeyState_Down == KeyState::Down) || (KeyState_Down == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_Skill_0>();
		return true;
	}

	KeyState KeyState_Left = Input::getInstance()->getKey(VK_LEFT);
	if ((KeyState_Left == KeyState::Down) || (KeyState_Left == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_Skill_0>();
		return true;
	}

	KeyState KeyState_Right = Input::getInstance()->getKey(VK_RIGHT);
	if ((KeyState_Right == KeyState::Down) || (KeyState_Right == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_Skill_0>();
		return true;
	}

	KeyState KeyState_X = Input::getInstance()->getKey('X');
	if ((KeyState_X == KeyState::Down) || (KeyState_X == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_Skill_0>();
		return true;
	}

	KeyState KeyState_Z = Input::getInstance()->getKey('Z');
	if ((KeyState_Z == KeyState::Down) || (KeyState_Z == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_Skill_0>();
		return true;
	}

	KeyState KeyState_C = Input::getInstance()->getKey('C');
	if ((KeyState_C == KeyState::Down) || (KeyState_C == KeyState::Hold))
	{
		user->changeCurrentState<UserState_Skill_0>();
		return true;
	}

	return true;
}

bool UserState_Idle::render()
{
	return true;
}

bool UserState_Idle::release()
{
	return true;
}
