#pragma once
#include "MapObject.hpp"

class Scene_InGame;

class Portal : public MapObject
{
protected:
	Scene_InGame* InGame = nullptr;

private:
	std::vector<std::wstring> textureKeyList;
	float beforeTime = 0.0f;
	float frameTime = 0.0f;
	float timeCounter = 0.0f;
	int state = 0;


public:
	std::wstring dstMapName;
	Vector2f dstPos;

public:
	Portal();
	Portal(Rect2f _rect);

private:
	bool Load(std::wstring _path);

public:
	void setScene(Scene_InGame* _InGame);
	void setDstMap(std::wstring _name);
	void setDstPos(Vector2f _pos);
	bool RectInPortal(Rect2f _target);
	bool WarpPortal();

public:
	virtual bool initialize() override;
	virtual bool frame(float _dt) override;
	virtual bool render() override;
	virtual bool release() override;
};