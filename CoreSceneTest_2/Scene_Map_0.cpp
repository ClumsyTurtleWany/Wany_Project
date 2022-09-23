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
		background->createShader(ShaderType::Texture);
		background->setTexture(pTexture);
		collisionMap = new QuadTree<float>;
		collisionMap->create(&rect);
		renderCamera->setBoundary(rect);

		background->mapWidth = width;
		background->mapHeight = height;

		background->renderCamera = renderCamera;
	}
	if (DXTextureManager::getInstance()->Load(USER_CHARACTER_0))
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(USER_CHARACTER_0);
		float width = pTexture->getWidth();
		float height = pTexture->getHeight();
		float x = (background->mapWidth - width) * 0.5f;
		float y = (background->mapHeight - height) * 0.5f;
		
		user = new Player(Rect2f(x, y, width, height));
		user->createShader(ShaderType::Texture);
		user->setTexture(pTexture);
	}

	user->currentMap = collisionMap;
	user->mapWidth = background->mapWidth;
	user->mapHeight = background->mapHeight;
	renderCamera->setPos(user->getCenter());
	user->setCamera(renderCamera);

	for (int i = 0; i < 0; i++)
	{
		Monster* pMonster = new Monster;
		pMonster->Random();
		pMonster->setColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
		pMonster->mapWidth = background->mapWidth;
		pMonster->mapHeight = background->mapHeight;

		MonsterList.push_back(pMonster);
		collisionMap->addObject(pMonster);
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
