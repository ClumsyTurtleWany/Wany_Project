#include "Map.hpp"
#include "UserState_Idle.hpp"

Map::Map()// : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>;
	//pObj->type = OBJECT_TYPE::STATIC_OBJECT;
	//pObj->createShader(ShaderType::Texture);
	this->type = OBJECT_TYPE::STATIC_OBJECT;
}

Map::Map(const Rect2f& _rect)// : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>(_rect);
	//pObj->type = OBJECT_TYPE::STATIC_OBJECT;
	//pObj->createShader(ShaderType::Texture);
	this->type = OBJECT_TYPE::STATIC_OBJECT;
	this->shape = _rect;

	collisionMap = new QuadTree<float>;
	collisionMap->create(&this->shape);
}

Map::~Map()
{
	release();
}

void Map::addMapObject(MapObject* _obj)
{
	mapObjectList.push_back(_obj);
}

void Map::addObject(object2D<float>* _obj)
{
	collisionMap->addObject(_obj);
}

bool Map::Collision(object2D<float>* _src, std::vector<object2D<float>*>* _dst, std::vector<Rect_<float>>* _dstSection)
{
	return collisionMap->Collision(_src, _dst, _dstSection);
}

bool Map::CollisionMapObject(object2D<float>* _obj, MapObjectType _targetType, std::vector<object2D<float>*>* _dst, std::vector<Rect_<float>>* _dstSection)
{
	bool isCollision = false;
	for (auto it : mapObjectList)
	{
		if ((it->type == _targetType))
		{
			Rect2f intersection;
			if (_obj->shape.intersectRect(it->shape, &intersection))
			{
				if (_dst != nullptr)
				{
					_dst->push_back(it);
				}

				if (_dstSection != nullptr)
				{
					_dstSection->push_back(intersection);
				}

				DrawBorder(it->shape, BORDER_COLOR_RED);
				isCollision = true;
			}
		}
		else
		{
			continue;
		}
	}
	return isCollision;
}

void Map::updateDynamicObject()
{
	collisionMap->updateDynamicObject();
}

void Map::updateShader()
{
	std::vector<Vertex>* list = pShader->getVertexList();
	list->at(0).pos = { -1.0f, 1.0f, 0.0f };
	list->at(1).pos = { 1.0f, 1.0f, 0.0f };
	list->at(2).pos = { -1.0f, -1.0f, 0.0f };
	list->at(3).pos = { 1.0f, -1.0f, 0.0f };

	list->at(0).color = { 1.0f, 1.0f, 1.0f, 0.5f };
	list->at(1).color = { 1.0f, 1.0f, 1.0f, 0.5f };
	list->at(2).color = { 1.0f, 1.0f, 1.0f, 0.5f };
	list->at(3).color = { 1.0f, 1.0f, 1.0f, 0.5f };

	if (renderCamera != nullptr)
	{
		Rect2f rectCamera = renderCamera->getRect();
		Rect2f rectTexture;
		rectTexture.LT.x = rectCamera.LT.x / mapWidth;
		rectTexture.LT.y = rectCamera.LT.y / mapHeight;
		rectTexture.RB.x = rectCamera.RB.x / mapWidth;
		rectTexture.RB.y = rectCamera.RB.y / mapHeight;

		list->at(0).texture = { rectTexture.LT.x, rectTexture.LT.y }; // p1-LT
		list->at(1).texture = { rectTexture.RB.x, rectTexture.LT.y }; // p2-RT
		list->at(2).texture = { rectTexture.LT.x, rectTexture.RB.y }; // p3-LB
		list->at(3).texture = { rectTexture.RB.x, rectTexture.RB.y }; // p4-RB
	}
}

void Map::updateShaderCamera()
{
	std::vector<Vertex>* list = pShader->getVertexList();
	list->at(0).pos = { -1.0f, 1.0f, 0.0f };
	list->at(1).pos = { 1.0f, 1.0f, 0.0f };
	list->at(2).pos = { -1.0f, -1.0f, 0.0f };
	list->at(3).pos = { 1.0f, -1.0f, 0.0f };

	list->at(0).color = { 1.0f, 1.0f, 1.0f, 0.5f };
	list->at(1).color = { 1.0f, 1.0f, 1.0f, 0.5f };
	list->at(2).color = { 1.0f, 1.0f, 1.0f, 0.5f };
	list->at(3).color = { 1.0f, 1.0f, 1.0f, 0.5f };

	if (renderCamera != nullptr)
	{
		Rect2f rectCamera = renderCamera->getRect();
		Rect2f rectTexture;
		rectTexture.LT.x = rectCamera.LT.x / mapWidth;
		rectTexture.LT.y = rectCamera.LT.y / mapHeight;
		rectTexture.RB.x = rectCamera.RB.x / mapWidth;
		rectTexture.RB.y = rectCamera.RB.y / mapHeight;

		list->at(0).texture = { rectTexture.LT.x, rectTexture.LT.y }; // p1-LT
		list->at(1).texture = { rectTexture.RB.x, rectTexture.LT.y }; // p2-RT
		list->at(2).texture = { rectTexture.LT.x, rectTexture.RB.y }; // p3-LB
		list->at(3).texture = { rectTexture.RB.x, rectTexture.RB.y }; // p4-RB
	}

}

bool Map::initialize()
{
	object2D<float>::initialize();

	return true;
}

bool Map::frame(float _dt)
{
	if (!object2D<float>::frame(_dt))
	{
		return false;
	}

	return true;
}

bool Map::render()
{
	if (!object2D<float>::render())
	{
		return false;
	}

	collisionMap->render();

	for (auto it : mapObjectList)
	{
		DrawBorder(it->shape, BORDER_COLOR_YELLOW);
	}

	return true;
}

bool Map::release()
{
	if (collisionMap != nullptr)
	{
		delete collisionMap;
		collisionMap = nullptr;
	}

	object2D<float>::release();
	return true; // currentState->release();
}