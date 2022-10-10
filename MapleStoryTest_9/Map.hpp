#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "QuadTree.hpp"
#include "Camera.hpp"
#include "MapObject.hpp"
#include "FMODSoundManager.hpp"
#include "DXTextureManager.hpp"
#include <filesystem>
#include <fstream>

class Player;
class NPC;
class Scene_InGame;
class Portal;

class Map : public object2D<float>
{
private:
	struct SpawnPoint
	{
		Vector2f pos;
		Rect2f boundary;
	};

	std::wstring mapName;

	QuadTree<float>* collisionMap = nullptr;
	FMODSound* BGM = nullptr;
	Vector2f currentUserPos;

	std::map<std::wstring, std::wstring> mapTextureList;
	std::vector<std::wstring> monsterNameList;
	std::vector<std::wstring> npcNameList;
	std::vector<NPC*> npcList;
	std::vector<SpawnPoint> spawnPointList;

	Player* user = nullptr;

	int maxMonster = 0;

	float beforeTime = 0.0f;
	float timeCounter = 0.0f;
	float spawnTime = 0.0f;

public:
	std::vector<MapObject*> mapObjectList;
	std::vector<Portal*> portalList;

public:
	Map();
	Map(const Rect2f& _rect);
	virtual ~Map();

private:
	bool CreateMonster(int _npcIdx, int _spawnIdx);

public:
	bool Load(std::wstring _path);
	bool LoadInfo(std::wstring _path);

public:
	void setMapName(std::wstring _name);
	std::wstring getMapName();
	void setUser(Player* _user);
	void setSceneToPortal(Scene_InGame* _InGame);
	void PlayBGM();
	void StopBGM();

public:
	bool Collision(object2D<float>* _src, std::vector<object2D<float>*>* _dst, std::vector<Rect_<float>>* _dstSection = nullptr);
	bool CollisionMapObject(object2D<float>* _obj, MapObjectType _targetType, std::vector<object2D<float>*>* _dst = nullptr, std::vector<Rect_<float>>* _dstSection = nullptr);
	bool CollisionPortal(object2D<float>* _obj, std::vector<Portal*>* _dst = nullptr);

public:
	virtual void updateShader() override;
	virtual void updateShaderCamera() override;

public:
	virtual bool initialize() override;
	virtual bool frame(float _dt) override;
	virtual bool render() override;
	virtual bool release() override;

};