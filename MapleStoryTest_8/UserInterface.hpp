#pragma once
#include "Object.hpp"
#include <filesystem>
#include <fstream>
#include "Player.hpp"

class UserInterface : public object2D<float>
{
public:
	enum class Type
	{
		Dialog,
		Button,
	};

public:
	struct Info
	{
		std::wstring textureKey;
		Vector2f pos;
	};

public:
	Vector2f pos;
	std::map<std::wstring, std::wstring> textureKeyMap;
	std::vector<Info> infoList;
	std::vector<UserInterface*> childList;
	std::map<std::wstring, std::map<std::wstring, std::wstring>> fontMapList;
	bool isClose = false;

	Player* user = nullptr;

public:
	UserInterface();
	UserInterface(UserInterface* _src);
	UserInterface(const Rect2f& _rect);
	virtual ~UserInterface();

public:
	virtual bool Load(std::wstring _path);
	virtual bool LoadInfo(std::wstring _path);
	virtual bool LoadFont(std::wstring _path, std::map<std::wstring, std::wstring>* _dst = nullptr);
	virtual bool LoadBtn(std::wstring _path);
	virtual void setPos(Vector2f _pos);
	virtual void setPlayer(Player* _user);
	virtual void addChild(UserInterface* _child);
	virtual void copy(UserInterface* _src);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

};