#pragma once
#include <iostream>
#include <iomanip> // std::cout << std::setw << std::left...
#include <conio.h>
#include "StudentMgr.h"

class UI
{
private:
	studentMgr* studentManager;

public:
	enum EMAINMENU
	{
		EN_INSERT_NEW_STUDENT = (int)48, // ascii 0 == 48
		EN_ERASE_STUDENT,
		EN_FIND_STUDENT,
		EN_SORT_STUDENT,
		EN_MAKE_DUMMY,
		EN_EXIT = (int)27 // ascii escape == 27
	};

	enum ESORTMODE
	{
		EN_SORT_ID_ASCENDING = 0,
		EN_SORT_ID_DECENDING,
		EN_SORT_NAME_ASCENDING,
		EN_SORT_NAME_DECENDING,
		EN_SORT_AGE_ASCENDING,
		EN_SORT_AGE_DECENDING,
		EN_SORT_SCORE_ASCENDING,
		EN_SORT_SCORE_DECENDING
	};

public:
	UI() : studentManager(nullptr) {};
	UI(studentMgr* _stuMgr) : studentManager(_stuMgr) {};
	~UI() { studentManager = nullptr; };

	void printData();
	void printStudentData(student& _student);
	void printMainMenu();
	void printSortMenu();
	void printInsertStudent();
	void eraseStudent();
	void findStudent();
	void sortStudent();
	void redraw();	
};