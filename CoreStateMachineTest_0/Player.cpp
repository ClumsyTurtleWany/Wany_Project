#include "Player.hpp"
#include "UserState_Idle.hpp"

Player::Player() : currentState(new UserState_Idle(this))
{

}

Player::~Player()
{

}

bool Player::frame(float _dt)
{
	return currentState->frame();
}

bool Player::render()
{
	return currentState->render();
}

