#include "UserState_Idle.hpp"
#include "UserState_Skill_0_1.hpp"
#include "UserState_Jump.hpp"
#include "UserState_MoveLeft.hpp"
#include "UserState_MoveRight.hpp"
#include "UserState_Falling.hpp"
#include "Player.hpp"
#include "SkillManager.hpp"
#include "UserState_Climb.hpp"

UserState_Idle::UserState_Idle(Player* _user) : UserState(_user)
{
	initialize();
}

bool UserState_Idle::initialize()
{
	textureKeyList.push_back(USER_CHARACTER_IDLE_0);
	textureKeyList.push_back(USER_CHARACTER_IDLE_1);
	textureKeyList.push_back(USER_CHARACTER_IDLE_2);
	textureKeyList.push_back(USER_CHARACTER_IDLE_1);

	for (auto it : textureKeyList)
	{
		if (!DXTextureManager::getInstance()->Load(it))
		{
			std::wstring debugStr = L"UserState_Idle::initailize::Failed Texture Load(";
			debugStr += it + L").\n";
			OutputDebugString(debugStr.c_str());
			return false;
		}
	}

	user->force.x = 0;
	user->force.y = 0;

	return true;
}

bool UserState_Idle::frame()
{
	float currentTime = Timer::getInstance()->getPlayTime();
	float frameTime = currentTime - beforeTime;
	effectTime += frameTime;
	if (effectTime >= 0.5f)
	{
		effectTime = 0.0f;
		idleState++;
	}
	beforeTime = currentTime;

	if (idleState >= textureKeyList.size())
	{
		idleState = 0;
	}

	user->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[idleState]));

	if (!user->currentMap->CollisionMapObject(user, MapObjectType::Floor))
	{
		user->changeCurrentState<UserState_Falling>();
		return true;
	}

	// Climb
	KeyState KeyState_Up = Input::getInstance()->getKey(VK_UP);
	if ((KeyState_Up == KeyState::Down) || (KeyState_Up == KeyState::Hold))
	{
		// 로프 충돌 체크
		if (user->currentMap->CollisionMapObject(user, MapObjectType::Rope))
		{
			user->changeCurrentState<UserState_Climb>();
			return true;
		}
		//user->shape.offset(Vector2f( 0.0f, -0.5f));
		//return true;
	}

	// Get Down
	KeyState KeyState_Down = Input::getInstance()->getKey(VK_DOWN);
	if ((KeyState_Down == KeyState::Down) || (KeyState_Down == KeyState::Hold))
	{
		// 로프 충돌 체크
		std::vector<object2D<float>*> collisionObjList;
		std::vector<Rect2f> collisionRectList;
		if (user->currentMap->CollisionMapObject(user, MapObjectType::Rope, &collisionObjList, &collisionRectList))
		{
			for (auto it : collisionObjList)
			{
				if (user->shape.bottom() <= it->shape.top())
				{
					user->changeCurrentState<UserState_Climb>();
					return true;
				}
			}
		}
		else
		{
			// Get Down
		}
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
		//user->changeCurrentState<UserState_Skill_0_1>();
		return true;
	}

	// Skill 0 Btn
	KeyState KeyState_C = Input::getInstance()->getKey('C');
	if ((KeyState_C == KeyState::Down) || (KeyState_C == KeyState::Hold))
	{
		SkillManager::getInstance()->activeSkill(L"Skill_0");
		//user->changeCurrentState<UserState_Skill_0_1>();
		return true;
	}

	return true;
}

bool UserState_Idle::render()
{
	std::wstring strUserState;
	strUserState += L"UserState: ";
	strUserState += L"UserState_Idle";
	DXWriter::getInstance()->draw(0, 100, strUserState);

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

		std::vector<Vertex>* list = user->pShader->getVertexList();
		list->at(0).texture = { 0.0f, 0.0f }; // LT
		list->at(1).texture = { 1.0f, 0.0f }; // RT
		list->at(2).texture = { 0.0f, 1.0f }; // LB
		list->at(3).texture = { 1.0f, 1.0f }; // RB
	}
	else
	{
		user->shape.offset(Vector2f(-1.0f, 0.0f));
	}

	return false;
}

bool UserState_Idle::moveRight()
{
	if (user->currentDirection != Player::Direction::Right)
	{
		user->currentDirection = Player::Direction::Right;

		std::vector<Vertex>* list = user->pShader->getVertexList();
		list->at(0).texture = { 1.0f, 0.0f }; // LT
		list->at(1).texture = { 0.0f, 0.0f }; // RT
		list->at(2).texture = { 1.0f, 1.0f }; // LB
		list->at(3).texture = { 0.0f, 1.0f }; // RB
	}
	else
	{
		user->shape.offset(Vector2f(1.0f, 0.0f));
	}

	return false;
}
