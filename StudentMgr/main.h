#pragma once
#include <thread>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "UI.h"
#include <fstream>

#define UP 

class Engine
{
private:
	studentMgr* studentManager;
	UI* mainUI;

public:
	Engine() : studentManager(nullptr), mainUI(nullptr) 
	{
		studentManager = new studentMgr;
		mainUI = new UI;
	};
	~Engine() 
	{
		delete studentManager;
		delete mainUI;
	};

	studentMgr* getManager() { return studentManager; };
	UI* getUI() { return mainUI; };

	// 0. Insert
	void insertNewStudent();
	 
	// 1. Erase
	void eraseStudent();
	
	// 2. Find
	
	// 3. Sort
	
	// 4. Dummy
	void makeDummyData();

	// 5. Save
	
	// 6. Load
	// file save, write data, file load, read data

};