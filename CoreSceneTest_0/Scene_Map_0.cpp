#include "Scene_Map_0.hpp"

bool Scene_Map_0::initialize()
{
	worldMap = new QuadTree<float>;
	RECT clientRect = g_pWindow->getClientRect();
	float width = clientRect.right - clientRect.left;
	float height = clientRect.bottom - clientRect.top;
	Rect2f rect(0, 0, width, height);
	worldMap->create(&rect);

	user = new Player(Rect2f(100, 100, 39, 35));
	if (DXTextureManager::getInstance()->Load(USER_CHARACTER_0))
	{
		user->pObj->setTexture(DXTextureManager::getInstance()->getTexture(USER_CHARACTER_0));
	}

	user->currentMap = worldMap;

	for (int i = 0; i < 10; i++)
	{
		Monster* pMonster = new Monster;
		pMonster->pObj->Random();
		pMonster->pObj->setColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));

		MonsterList.push_back(pMonster);
		worldMap->addObject(pMonster->pObj);
	}

	return true;
}

//bool Scene_Map_0::frame()
//{
//	user->frame(Timer::getInstance()->getDeltaTime());
//
//	for (auto it : enemyList)
//	{
//		it->frame();
//	}
//
//	for (auto it : NPCList)
//	{
//		it->frame();
//	}
//
//	return false;
//}
//
//bool Scene_Map_0::render()
//{
//	return false;
//}
//
//bool Scene_Map_0::release()
//{
//	return false;
//}
