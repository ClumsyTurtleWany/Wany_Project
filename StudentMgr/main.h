#pragma once
#include <thread>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "UI.h"

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
	// print data
	// create dummy data for debug.
	// ui
	// control
	void makeDummyData(int _cnt);
};

void keyInputThread(Engine* _Engine);


void Engine::makeDummyData(int _cnt)
{
	for (int i = 0; i < _cnt; i++)
	{
		//char spell_1 = rand() % 25 + 65;
		//char spell_2 = rand() % 25 + 65;
		//char spell_3 = rand() % 25 + 65;
		std::string name;
		name.push_back(rand() % 25 + 65);
		name.push_back(rand() % 25 + 65);
		name.push_back(rand() % 25 + 65);

		int age = rand() % 47 + 18;

		student DummyStudent(name, age);
		DummyStudent.setScore(ESUBJECT::EN_KOR, rand() % 101);
		DummyStudent.setScore(ESUBJECT::EN_ENG, rand() % 101);
		DummyStudent.setScore(ESUBJECT::EN_MATH, rand() % 101);
		DummyStudent.setScore(ESUBJECT::EN_SOCI, rand() % 101);
		DummyStudent.setScore(ESUBJECT::EN_SCI, rand() % 101);

		studentManager->insertStudent(DummyStudent);
	}
}
