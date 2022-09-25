#include "MapObject.hpp"

MapObject::MapObject()// : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>;
	//pObj->type = OBJECT_TYPE::STATIC_OBJECT;
	//pObj->createShader(ShaderType::Texture);
}

MapObject::MapObject(const Rect2f& _rect, MapObjectType _type)// : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>(_rect);
	//pObj->type = OBJECT_TYPE::STATIC_OBJECT;
	//pObj->createShader(ShaderType::Texture);
	this->shape = _rect;
	type = _type;
}

MapObject::~MapObject()
{
	release();
}

//void MapObject::updateShader()
//{
//	std::vector<Vertex>* list = pShader->getVertexList();
//	list->at(0).pos = { -1.0f, 1.0f, 0.0f };
//	list->at(1).pos = { 1.0f, 1.0f, 0.0f };
//	list->at(2).pos = { -1.0f, -1.0f, 0.0f };
//	list->at(3).pos = { 1.0f, -1.0f, 0.0f };
//
//	if (renderCamera != nullptr)
//	{
//		Rect2f rectCamera = renderCamera->getRect();
//		Rect2f rectTexture;
//		rectTexture.LT.x = rectCamera.LT.x / mapWidth;
//		rectTexture.LT.y = rectCamera.LT.y / mapHeight;
//		rectTexture.RB.x = rectCamera.RB.x / mapWidth;
//		rectTexture.RB.y = rectCamera.RB.y / mapHeight;
//
//		list->at(0).texture = { rectTexture.LT.x, rectTexture.LT.y }; // p1-LT
//		list->at(1).texture = { rectTexture.RB.x, rectTexture.LT.y }; // p2-RT
//		list->at(2).texture = { rectTexture.LT.x, rectTexture.RB.y }; // p3-LB
//		list->at(3).texture = { rectTexture.RB.x, rectTexture.RB.y }; // p4-RB
//	}
//}
//
//void MapObject::updateShaderCamera()
//{
//	std::vector<Vertex>* list = pShader->getVertexList();
//	list->at(0).pos = { -1.0f, 1.0f, 0.0f };
//	list->at(1).pos = { 1.0f, 1.0f, 0.0f };
//	list->at(2).pos = { -1.0f, -1.0f, 0.0f };
//	list->at(3).pos = { 1.0f, -1.0f, 0.0f };
//
//	if (renderCamera != nullptr)
//	{
//		Rect2f rectCamera = renderCamera->getRect();
//		Rect2f rectTexture;
//		rectTexture.LT.x = rectCamera.LT.x / mapWidth;
//		rectTexture.LT.y = rectCamera.LT.y / mapHeight;
//		rectTexture.RB.x = rectCamera.RB.x / mapWidth;
//		rectTexture.RB.y = rectCamera.RB.y / mapHeight;
//
//		list->at(0).texture = { rectTexture.LT.x, rectTexture.LT.y }; // p1-LT
//		list->at(1).texture = { rectTexture.RB.x, rectTexture.LT.y }; // p2-RT
//		list->at(2).texture = { rectTexture.LT.x, rectTexture.RB.y }; // p3-LB
//		list->at(3).texture = { rectTexture.RB.x, rectTexture.RB.y }; // p4-RB
//	}
//
//}


//
//bool MapObject::initialize()
//{
//	return true;
//}
//
//bool MapObject::frame(float _dt)
//{
//	if (!pObj->frame(_dt))
//	{
//		return false;
//	}
//
//	return true;
//}
//
//bool MapObject::render()
//{
//	if (!pObj->render())
//	{
//		return false;
//	}
//
//	return true;
//}
//
//bool MapObject::release()
//{
//	pObj->release();
//	delete pObj;
//	pObj = nullptr;
//	return true; // currentState->release();
//}