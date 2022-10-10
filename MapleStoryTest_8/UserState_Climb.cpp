#include "UserState_Climb.hpp"
#include "Player.hpp"
#include "UserState_Skill_0_1.hpp"
#include "UserState_MoveLeft.hpp"
#include "UserState_MoveRight.hpp"
#include "UserState_Falling.hpp"
#include "SkillManager.hpp"

UserState_Climb::UserState_Climb(Player* _user) : UserState(_user)
{
	initialize();
}

bool UserState_Climb::initialize()
{
	textureKeyList.push_back(USER_CHARACTER_JUMP_0);

	for (auto it : textureKeyList)
	{
		if (!DXTextureManager::getInstance()->Load(it))
		{
			std::wstring debugStr = L"UserState_Jump::initailize::Failed Texture Load(";
			debugStr += it + L").\n";
			OutputDebugString(debugStr.c_str());
			return false;
		}
	}

	user->force.x = 0;
	user->force.y = 0;

	collisionRope = nullptr;
	collisionFloor = nullptr;
	std::vector<object2D<float>*> collisionObjList;
	std::vector<Rect2f> collisionRectList;
	if (user->currentMap->CollisionMapObject(user, MapObjectType::Rope, &collisionObjList, &collisionRectList))
	{
		for (auto it : collisionObjList)
		{
			collisionRope = it;
			break;
		}
	}
	else
	{
		user->changeCurrentState<UserState_Idle>();
	}

	user->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[state]));
	//user->force.y = -300.0f;
	beforeTime = Timer::getInstance()->getPlayTime();

	return true;
}

bool UserState_Climb::frame()
{
	/*float currentTime = Timer::getInstance()->getPlayTime();
	float frameTime = currentTime - beforeTime;
	timeCounter += frameTime;

	if (timeCounter >= 0.33f)
	{
		timeCounter = 0.0f;
		user->force.y -= user->force.y * 0.8f;
	}

	beforeTime = currentTime;

	if (user->force.y > -100.0f)
	{
		user->force.y = 0.0f;
		int a = 0;
		user->changeCurrentState<UserState_Falling>();
		return true;
	}*/
	

	// Climb
	KeyState KeyState_Up = Input::getInstance()->getKey(VK_UP);
	if ((KeyState_Up == KeyState::Down) || (KeyState_Up == KeyState::Hold))
	{
		if (collisionRope != nullptr)
		{
			if (user->shape.bottom() <= collisionRope->shape.top())
			{
				user->changeCurrentState<UserState_Idle>();
				return true;
			}
			else
			{
				user->shape.offset(Vector2f(0.0f, -0.2f));
			}

			return true;
		}
		
	}

	// Get Down
	KeyState KeyState_Down = Input::getInstance()->getKey(VK_DOWN);
	if ((KeyState_Down == KeyState::Down) || (KeyState_Down == KeyState::Hold))
	{
		if (collisionRope != nullptr)
		{
			if (user->shape.top() >= collisionRope->shape.bottom())
			{
				user->changeCurrentState<UserState_Falling>();
				return true;
			}
			else
			{
				user->shape.offset(Vector2f(0.0f, 0.2f));

				std::vector<object2D<float>*> collisionObjList;
				std::vector<Rect2f> collisionRectList;
				if (user->currentMap->CollisionMapObject(user, MapObjectType::Floor, &collisionObjList, &collisionRectList))
				{
					for (auto it : collisionObjList)
					{
						if (it->shape.top() >= collisionRope->shape.bottom())
						{
							collisionFloor = it;
							user->moveTo(user->shape.left(), it->shape.top() - user->shape.height() + 1);
							user->changeCurrentState<UserState_Idle>();
							return true;
						}
					}
				}
				else
				{
					collisionFloor = nullptr;
				}
			}
		}
	}

	// Move to Left
	KeyState KeyState_Jump = Input::getInstance()->getKey('X');
	KeyState KeyState_Left = Input::getInstance()->getKey(VK_LEFT);
	if (((KeyState_Left == KeyState::Down) || (KeyState_Left == KeyState::Hold)) &&
		((KeyState_Jump == KeyState::Down) || (KeyState_Jump == KeyState::Hold)))
	{
		user->force.x = -300;
		user->force.y = -100;
		if (user->currentDirection != Player::Direction::Left)
		{
			user->currentDirection = Player::Direction::Left;
			user->flipTexture(true);
		}
		user->changeCurrentState<UserState_Falling>();
		return true;
	}

	// Move to Right
	KeyState KeyState_Right = Input::getInstance()->getKey(VK_RIGHT);
	if (((KeyState_Right == KeyState::Down) || (KeyState_Right == KeyState::Hold)) &&
		((KeyState_Jump == KeyState::Down) || (KeyState_Jump == KeyState::Hold)))
	{
		user->force.x = 300;
		user->force.y = -100;
		if (user->currentDirection != Player::Direction::Right)
		{
			user->currentDirection = Player::Direction::Right;
			user->flipTexture(true);
		}
		user->changeCurrentState<UserState_Falling>();
		return true;
	}

	if (collisionRope != nullptr)
	{
		if (user->shape.bottom() <= collisionRope->shape.top())
		{
			user->changeCurrentState<UserState_Idle>();
			return true;
		}
	}

	if (collisionFloor != nullptr)
	{
		if (collisionFloor->shape.top() >= collisionRope->shape.bottom())
		{
			user->moveTo(user->shape.left(), collisionFloor->shape.top() - user->shape.height() + 1);
			user->changeCurrentState<UserState_Idle>();
			return true;
		}
	}

	return true;
}

bool UserState_Climb::render()
{
	/*std::wstring strUserState;
	strUserState += L"UserState: ";
	strUserState += L"UserState_Climb";
	DXWriter::getInstance()->draw(0, 100, strUserState);*/

	return true;
}

bool UserState_Climb::release()
{
	return true;
}
