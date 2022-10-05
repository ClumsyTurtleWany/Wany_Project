#pragma once
#include "NPC.hpp"
#include <filesystem>
#include "DXTextureManager.hpp"

class NPCManager : public Singleton<NPCManager>
{
private:
	friend class Singleton<NPCManager>;

private:
	//std::map<std::wstring, std::unique_ptr<NPC>> npcList;
	//std::vector<NPC*> jobList;

	std::map<std::wstring, NPCInfo> infoList;
	std::map<std::wstring, std::map<std::wstring, std::vector<std::wstring>>> textureKeyMapList;
	std::map<std::wstring, std::map<std::wstring, std::vector<Rect2f>>> spriteMapList;
	std::map<std::wstring, std::map<std::wstring, std::vector<Rect2f>>> spriteHitboxMapList;
	std::map<std::wstring, std::map<std::wstring, Vector2f>> spriteOffsetMapList;

	std::vector<NPC*> NPCList;

	Camera* renderCamera;

private:
	bool LoadNPC(std::wstring _path, std::wstring _key);
	bool LoadTexture(std::wstring _path, std::vector<std::wstring>& _list);
	bool LoadInfo(std::wstring _path, std::wstring _key);
	bool LoadSprite(std::wstring _path, std::wstring _key);

public:
	bool Load(std::wstring _path);

	void setCamera(Camera* _camera);
	NPCInfo getNPCInfo(std::wstring _name);
	bool getTextureKeyMap(std::wstring _name, std::map<std::wstring, std::vector<std::wstring>>& _map);
	bool getSpriteMap(std::wstring _name, std::map<std::wstring, std::vector<Rect2f>>& _map);
	bool getSpriteHitboxMap(std::wstring _name, std::map<std::wstring, std::vector<Rect2f>>& _map);
	bool getSpriteOffsetMap(std::wstring _name, std::map<std::wstring, Vector2f>& _map);
	NPC* CreateNPC(std::wstring _name);
	//bool addMonsterToJobList(Vector2f _pos, std::wstring _name);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};