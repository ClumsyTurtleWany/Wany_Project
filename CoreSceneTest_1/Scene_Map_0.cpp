#include "Scene_Map_0.hpp"

bool Scene_Map_0::initialize()
{
	Scene::initialize();
	// Create Background Map.
	if (DXTextureManager::getInstance()->Load(MAP_SCENE_0))
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(MAP_SCENE_0);
		float width = pTexture->getWidth();
		float height = pTexture->getHeight();
		Rect2f rect(0, 0, width, height);
		background = new BackgroundMap(rect);
		background->pObj->setTexture(pTexture);
		collisionMap = new QuadTree<float>;
		collisionMap->create(&rect);
		renderCamera.setBoundary(rect);

		background->pObj->mapWidth = width;
		background->pObj->mapHeight = height;
	}

	user = new Player(Rect2f(100, 100, 39, 35));
	if (DXTextureManager::getInstance()->Load(USER_CHARACTER_0))
	{
		user->pObj->setTexture(DXTextureManager::getInstance()->getTexture(USER_CHARACTER_0));
	}

	user->currentMap = collisionMap;
	user->pObj->mapWidth = background->pObj->mapWidth;
	user->pObj->mapHeight = background->pObj->mapHeight;

	for (int i = 0; i < 10; i++)
	{
		Monster* pMonster = new Monster;
		pMonster->pObj->Random();
		pMonster->pObj->setColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
		pMonster->pObj->mapWidth = background->pObj->mapWidth;
		pMonster->pObj->mapHeight = background->pObj->mapHeight;

		MonsterList.push_back(pMonster);
		collisionMap->addObject(pMonster->pObj);
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
