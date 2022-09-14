#include "UserState_Idle.hpp"
#include "UserState_Skill_0.hpp"
#include "UserState_Jump.hpp"
#include "UserState_MoveLeft.hpp"
#include "UserState_MoveRight.hpp"
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
	// Climb
	KeyState KeyState_Up = Input::getInstance()->getKey(VK_UP);
	if ((KeyState_Up == KeyState::Down) || (KeyState_Up == KeyState::Hold))
	{
		user->pObj->shape.offset(Vector2f( 0.0f, -1.0f));
		//return true;
	}

	// Get Down
	KeyState KeyState_Down = Input::getInstance()->getKey(VK_DOWN);
	if ((KeyState_Down == KeyState::Down) || (KeyState_Down == KeyState::Hold))
	{
		user->pObj->shape.offset(Vector2f(0.0f, 1.0f));
		//return true;
	}

	// Move to Left
	KeyState KeyState_Left = Input::getInstance()->getKey(VK_LEFT);
	if ((KeyState_Left == KeyState::Down) || (KeyState_Left == KeyState::Hold))
	{
		user->changeCurrentState<UserState_MoveLeft>();
		return true;
	}

	// Move to Right
	KeyState KeyState_Right = Input::getInstance()->getKey(VK_RIGHT);
	if ((KeyState_Right == KeyState::Down) || (KeyState_Right == KeyState::Hold))
	{
		user->changeCurrentState<UserState_MoveRight>();
		return true;
	}

	// Jump
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
		//user->changeCurrentState<UserState_Skill_0>();
		return true;
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

bool UserState_Idle::render()
{
	return true;
}

bool UserState_Idle::release()
{
	return true;
}

bool UserState_Idle::moveLeft()
{
	if (user->currentDirection != Player::Direction::Left)
	{
		user->currentDirection = Player::Direction::Left;

		std::vector<Vertex>* list = user->pObj->pShader->getVertexList();
		list->at(0).texture = { 0.0f, 0.0f }; // LT
		list->at(1).texture = { 1.0f, 0.0f }; // RT
		list->at(2).texture = { 0.0f, 1.0f }; // LB
		list->at(3).texture = { 1.0f, 1.0f }; // RB
	}
	else
	{
		user->pObj->shape.offset(Vector2f(-1.0f, 0.0f));
	}

	return false;
}

bool UserState_Idle::moveRight()
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

	return false;
}
