#pragma once
#include "GameCore.hpp"
#include "SelectModelServer.h"
#include <atlconv.h>

//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public WindowUI
{
public:
	HWND EditBoxHandle;
	HWND ListBoxHandle;
	HWND ButtonHandle;

	SocketNetwork::SelectModelServer* MainServer;

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();
	
public:
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	virtual bool run() override;
	virtual void Print(std::string msg, ...);
};