#include "UserState_Falling.hpp"
#include "Player.hpp"
#include "UserState_Skill_0_1.hpp"
#include "UserState_MoveLeft.hpp"
#include "UserState_MoveRight.hpp"
#include "SkillManager.hpp"
#include "EffectManager.hpp"
#include "UserState_Climb.hpp"

UserState_Falling::UserState_Falling(Player* _user) : UserState(_user)
{
    initialize();
}

bool UserState_Falling::initialize()
{
    textureKeyList.push_back(USER_CHARACTER_JUMP_0);

    for (auto it : textureKeyList)
    {
        if (!DXTextureManager::getInstance()->Load(it))
        {
            std::wstring debugStr = L"UserState_Falling::initailize::Failed Texture Load(";
            debugStr += it + L").\n";
            OutputDebugString(debugStr.c_str());
            return false;
        }
    }

    user->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[jumpState]));
	user->force.y = 0.0f;

	fallingHeight = user->shape.bottom();

	beforeTime = Timer::getInstance()->getPlayTime();

    return true;
}

bool UserState_Falling::frame()
{
	float currentTime = Timer::getInstance()->getPlayTime();
	float frameTime = currentTime - beforeTime;
	timeCounter += frameTime;

	if (timeCounter >= 0.1f)
	{
		timeCounter = 0.0f;
		user->force.y += (9.81f) * 5.0f;
		user->force.y = user->force.y >= 500.0f ? 500.0f : user->force.y;
	}

	beforeTime = currentTime;

	std::vector<object2D<float>*> collisionObjectList;
	std::vector<Rect2f> intersectionRectList;
	if (user->currentMap->CollisionMapObject(user, MapObjectType::Floor, &collisionObjectList, &intersectionRectList))
	{
		//user->force.x = 0.0f;
		//user->force.y = 0.0f;
		if (!collisionObjectList.empty())
		{
			for (auto it : collisionObjectList)
			{
				// floor y 100
				// user y 200
				// it->shape.bottom() < user->shape.bottom()
				if (fallingHeight <= it->shape.top())
				{
					if (user->shape.bottom() >= it->shape.top())
					{
						user->force.x = 0.0f;
						user->force.y = 0.0f;
						user->moveTo(user->shape.left(), it->shape.top() - user->shape.height() + 1);
						user->changeCurrentState<UserState_Idle>();
						return true;
					}
				}
				
			}
			//auto it = intersectionRectList.begin();
			//user->moveTo(it->left(), it->top() - user->shape.height() + 1);
			//user->moveTo(user->shape.left(), it->top() - user->shape.height() + 1);
			
		}
		//user->changeCurrentState<UserState_Idle>();
		//return true;
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

		KeyState KeyState_X = Input::getInstance()->getKey('X');
		if ((KeyState_X == KeyState::Down)/* || (KeyState_X == KeyState::Hold)*/)
		{
			KeyState_X = Input::getInstance()->getKey('X');
			if ((KeyState_X == KeyState::Up))
			{
				user->force.y = -100.0f;
				return true;
			}
			//user->changeCurrentState<UserState_Jump>();
		}

		//user->force.x = 0.0f;
		//user->force.y = 0.0f;
		//user->shape.offset(Vector2f(0.0f, -0.1f));
		//return true;
	}

	// Get Down
	KeyState KeyState_Down = Input::getInstance()->getKey(VK_DOWN);
	if ((KeyState_Down == KeyState::Down) || (KeyState_Down == KeyState::Hold))
	{
		//user->shape.offset(Vector2f(0.0f, 0.1f));
		//return true;
	}

	// Move to Left
	KeyState KeyState_Left = Input::getInstance()->getKey(VK_LEFT);
	if ((KeyState_Left == KeyState::Down) || (KeyState_Left == KeyState::Hold))
	{
		if (user->currentDirection != Player::Direction::Left)
		{
			user->currentDirection = Player::Direction::Left;
			user->flipTexture(true);
		}
		//user->currentDirection = Player::Direction::Left;
		//user->flipTexture(true);
		//user->changeCurrentState<UserState_MoveLeft>();
		//return true;
	}

	// Move to Right
	KeyState KeyState_Right = Input::getInstance()->getKey(VK_RIGHT);
	if ((KeyState_Right == KeyState::Down) || (KeyState_Right == KeyState::Hold))
	{
		if (user->currentDirection != Player::Direction::Right)
		{
			user->currentDirection = Player::Direction::Right;
			user->flipTexture(true);
		}
		//user->currentDirection = Player::Direction::Right;
		//user->flipTexture(true);
		//user->changeCurrentState<UserState_MoveRight>();
		//return true;
	}

	// Jump
	KeyState KeyState_X = Input::getInstance()->getKey('X');
	if ((beforeJumpKeyState == KeyState::Up) || (beforeJumpKeyState == KeyState::Free))
	{
		if ((KeyState_X == KeyState::Down) || (KeyState_X == KeyState::Hold))
		{
			if (!user->doubleJump)
			{
				user->doubleJump = true;
				SkillManager::getInstance()->addSkillToJobList(L"DoubleJump");
				float force_x = 300.0f;
				user->force.x = user->currentDirection == Player::Direction::Left ? -force_x : force_x;
				user->force.y = -50.0f;
				return true;
			}
		}
	}
	beforeJumpKeyState = KeyState_X;

	// Skill 0 Btn
	KeyState KeyState_C = Input::getInstance()->getKey('C');
	if ((KeyState_C == KeyState::Down) || (KeyState_C == KeyState::Hold))
	{
		SkillManager::getInstance()->addSkillToJobList(L"Skill_0");
		//user->changeCurrentState<UserState_Skill_0_1>();
		return true;
	}

	// Skill 1 Btn
	KeyState KeyState_D = Input::getInstance()->getKey('D');
	if ((KeyState_D == KeyState::Down) || (KeyState_D == KeyState::Hold))
	{
		SkillManager::getInstance()->addSkillToJobList(L"Skill_1");
		return true;
	}

	// Skill 2 Btn
	KeyState KeyState_F = Input::getInstance()->getKey('F');
	if ((KeyState_F == KeyState::Down) || (KeyState_F == KeyState::Hold))
	{
		SkillManager::getInstance()->addSkillToJobList(L"Skill_2");
		return true;
	}


    //user->changeCurrentState<UserState_Idle>();
    return true;
}

bool UserState_Falling::render()
{
	std::wstring strUserState;
	strUserState += L"UserState: ";
	strUserState += L"UserState_Falling";
	DXWriter::getInstance()->draw(0, 100, strUserState);

    return true;
}

bool UserState_Falling::release()
{
    return true;
}