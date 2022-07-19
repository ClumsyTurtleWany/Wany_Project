#pragma once
#include <thread>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "UI.h"
#include <fstream>


class Engine
{
private:
	studentMgr* studentManager;
	UI* mainUI;

public:
	Engine() : studentManager(nullptr), mainUI(nullptr) 
	{
		studentManager = new studentMgr;
		mainUI = new UI(studentManager);
	};
	~Engine() 
	{
		delete studentManager;
		delete mainUI;
	};

	studentMgr* getMgr() { return studentManager; };
	UI* getUI() { return mainUI; };

	// file save, write data, file load, read data
	
	
	// create dummy data for debug.
	void makeDummyData(int _cnt);
	//void insertStudent();
	void findName();
	
	
};

//void keyInputThread(Engine* _Engine);


