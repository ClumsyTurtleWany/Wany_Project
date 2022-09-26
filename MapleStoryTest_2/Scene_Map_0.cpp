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
		background = new Map(rect);
		background->createShader(ShaderType::Texture);
		background->setTexture(pTexture);
		//collisionMap = new QuadTree<float>;
		//collisionMap->create(&rect);
		renderCamera->setBoundary(rect);

		background->mapWidth = width;
		background->mapHeight = height;

		background->renderCamera = renderCamera;
		DXShaderBorderManager::getInstance()->setMapSize(Vector2f(width, height));

		// 중앙 상단 발판 545, 455, 1048, 20 - 로프1 618, 455, 10, 222,  로프2  1499, 455, 10, 222
		MapObject* Stepbox_0 = new MapObject(Rect2f(545, 455, 1048, 20), MapObjectType::Floor);
		MapObject* Stepbox_0_rope_0 = new MapObject(Rect2f(618, 455, 10, 222), MapObjectType::Rope);
		MapObject* Stepbox_0_rope_1 = new MapObject(Rect2f(1499, 455, 10, 222), MapObjectType::Rope);
		background->addMapObject(Stepbox_0);
		background->addMapObject(Stepbox_0_rope_0);
		background->addMapObject(Stepbox_0_rope_1);

		// 왼쪽 상단 발판 0, 723, 836, 20 - 로프 64, 723, 10, 257
		MapObject* Stepbox_1 = new MapObject(Rect2f(0, 723, 836, 20), MapObjectType::Floor);
		MapObject* Stepbox_1_rope_0 = new MapObject(Rect2f(64, 723, 10, 257), MapObjectType::Rope);
		background->addMapObject(Stepbox_1);
		background->addMapObject(Stepbox_1_rope_0);

		// 왼쪽 하단 발판 0, 1024, 750, 20 - 로프 604, 1024, 10, 185
		MapObject* Stepbox_2 = new MapObject(Rect2f(0, 1024, 750, 20), MapObjectType::Floor);
		MapObject* Stepbox_2_rope_0 = new MapObject(Rect2f(604, 1024, 10, 185), MapObjectType::Rope);
		background->addMapObject(Stepbox_2);
		background->addMapObject(Stepbox_2_rope_0);

		// 오른쪽 상단 발판 1255, 723, 840, 20 - 로프 2016, 723, 10, 257
		MapObject* Stepbox_3 = new MapObject(Rect2f(1255, 723, 840, 20), MapObjectType::Floor);
		MapObject* Stepbox_3_rope_0 = new MapObject(Rect2f(2016, 723, 10, 257), MapObjectType::Rope);
		background->addMapObject(Stepbox_3);
		background->addMapObject(Stepbox_3_rope_0);

		// 오른쪽 하단 발판 1345, 1024, 750, 20 - 로프 1485, 1024, 10, 185
		MapObject* Stepbox_4 = new MapObject(Rect2f(1345, 1024, 750, 20), MapObjectType::Floor);
		MapObject* Stepbox_4_rope_0 = new MapObject(Rect2f(1485, 1024, 10, 185), MapObjectType::Rope);
		background->addMapObject(Stepbox_4);
		background->addMapObject(Stepbox_4_rope_0);

		// 바닥 0, 1255, 2095, 155
		MapObject* floor = new MapObject(Rect2f(0, 1255, 2095, 155), MapObjectType::Floor);
		background->addMapObject(floor);
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

	user->currentMap = background;
	user->mapWidth = background->mapWidth;
	user->mapHeight = background->mapHeight;
	renderCamera->setPos(user->getCenter());
	user->setCamera(renderCamera);

	SkillManager::getInstance()->setUser(user);
	SkillManager::getInstance()->LoadDir(SKILL_DIRECTORY);
	for (auto it : SkillManager::getInstance()->skillNameList)
	{
		Skill* pSkill = SkillManager::getInstance()->getSkill(it);

		if (pSkill != nullptr)
		{
			int a = 0;
		}
		else
		{
			int a = 0;
		}

	}


	for (int i = 0; i < 10; i++)
	{
		Monster* pMonster = new Monster;
		pMonster->Random();
		pMonster->setColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
		pMonster->mapWidth = background->mapWidth;
		pMonster->mapHeight = background->mapHeight;

		MonsterList.push_back(pMonster);
		background->addObject(pMonster);
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
