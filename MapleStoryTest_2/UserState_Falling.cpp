#include "UserState_Falling.hpp"
#include "Player.hpp"
#include "UserState_Skill_0_1.hpp"
#include "UserState_MoveLeft.hpp"
#include "UserState_MoveRight.hpp"
#include "SkillManager.hpp"

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
		user->force.y += (9.81f + user->force.y) * 5.0f;
		user->force.y = user->force.y >= 500.0f ? 500.0f : user->force.y;
	}

	beforeTime = currentTime;

	std::vector<object2D<float>*> collisionObjectList;
	std::vector<Rect2f> intersectionRectList;
	if (user->currentMap->CollisionMapObject(user, MapObjectType::Floor, &collisionObjectList, &intersectionRectList))
	{
		//user->force.x = 0.0f;
		//user->force.y = 0.0f;
		if (!intersectionRectList.empty())
		{
			for (auto it : intersectionRectList)
			{
				if (it.bottom() >= user->shape.bottom())
				{
					user->force.x = 0.0f;
					user->force.y = 0.0f;
					user->moveTo(user->shape.left(), it.top() - user->shape.height() + 1);
					user->changeCurrentState<UserState_Idle>();
					return true;
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
	if ((KeyState_X == KeyState::Down) || (KeyState_X == KeyState::Hold))
	{
		//user->changeCurrentState<UserState_Falling>();
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



    //user->changeCurrentState<UserState_Idle>();
    return true;
}

bool UserState_Falling::render()
{
    return true;
}

bool UserState_Falling::release()
{
    return true;
}