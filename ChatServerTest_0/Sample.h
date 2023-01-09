#pragma once
#include "GameCore.hpp"
#include "ChatServer.h"

//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public WindowUI
{
public:
	//bool initialize() override;
	//bool frame() override;
	//bool render() override;
	//bool release() override;
	HWND EditBoxHandle;
	HWND ListBoxHandle;
	HWND ButtonHandle;

	ChatServer MainServer;

public:
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	virtual bool run() override;
};