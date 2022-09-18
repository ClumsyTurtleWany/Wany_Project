#include "Player.hpp"
#include "UserState_Idle.hpp"

Player::Player() : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>;
	//pObj->createShader(ShaderType::Texture);
}

Player::Player(const Rect2f& _rect) : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>(_rect);
	//pObj->createShader(ShaderType::Texture);
	shape = _rect;
}

Player::~Player()
{
	release();
}

bool Player::initialize()
{
	return true;
}

bool Player::frame(float _dt)
{
	object2D<float>::frame(_dt);
	/*if (!pObj->frame(_dt))
	{
		return false;
	}*/

	if (!currentState->frame())
	{
		return false;
	}

	//renderCamera->setPos(shape.center());
	//pObj->hitbox = pObj->shape;
	hitbox = shape;

	return true;
}

bool Player::render()
{
	object2D<float>::render();
	/*if (!pObj->render())
	{
		return false;
	}*/

	DrawBorder(hitbox, BORDER_COLOR_RED);

	if (!currentState->render())
	{
		return false;
	}

	return true;
}

bool Player::release()
{
	//pObj->release();
	//delete pObj;
	//pObj = nullptr;
	return currentState->release();
}

void Player::updateShader()
{
	Rect_<float> rectNDC;
	rectNDC = ScreenToNDC();

	if (renderCamera != nullptr)
	{
		float magnification_width = mapWidth / renderCamera->getWidth();
		float magnification_Height = mapHeight / renderCamera->getHeight();
		rectNDC.LT.x *= magnification_width;
		rectNDC.LT.y *= magnification_Height;
		rectNDC.RB.x *= magnification_width;
		rectNDC.RB.y *= magnification_Height;
	}
	//rectNDC = ScreenToCamera();

	// Vectex List
	std::vector<Vertex>* list = pShader->getVertexList();
	list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
	list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
	list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
	list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

	//list->at(0).texture = { 0.0f, 0.0f }; // p1-LT
	//list->at(1).texture = { 1.0f, 0.0f }; // p2-RT
	//list->at(2).texture = { 0.0f, 1.0f }; // p3-LB
	//list->at(3).texture = { 1.0f, 1.0f }; // p4-RB
}

void Player::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

Rect2f Player::getRect()
{
	return shape;
}

Vector2f Player::getCenter()
{
	return shape.center();
}
