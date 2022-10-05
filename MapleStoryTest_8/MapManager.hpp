#pragma once
#include "Map.hpp"
#include <filesystem>


class MapManager : public Singleton<MapManager>
{
private:
	friend class Singleton<MapManager>;

private:
	std::map<std::wstring, std::unique_ptr<Map>> mapList;

	Camera* renderCamera;

public:
	bool Load(std::wstring _path);
	void setCamera(Camera* _camera);
	Map* getMap(std::wstring _name);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};