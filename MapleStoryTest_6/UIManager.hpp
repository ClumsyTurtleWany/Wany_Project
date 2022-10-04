#pragma once
#include "UserInterface.hpp"

class UIManager : public Singleton< UIManager>
{
private:
	friend class Singleton<UIManager>;

private:
	std::map<std::wstring, std::unique_ptr<UserInterface>> uiList;
	std::vector<UserInterface*> jobList;

public:
	bool Load(std::wstring _path);
	UserInterface* CreateUI(Vector2f _pos, std::wstring _name);
	UserInterface* getUI(std::wstring _name);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};