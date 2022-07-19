#pragma once
#include <iostream>
#include <iomanip> // std::cout << std::setw << std::left...
#include <conio.h>
#include "StudentMgr.h"

#define NUM_KEY (int)48 // ascii 0 == 48
#define ESC_KEY (int)27 // ascii escape == 27

class UI
{
private:
	studentMgr* studentManager;

	int width_ID = 5;
	int width_Name = 7;
	int width_Age = 6;
	int width_Kor = 6;
	int width_Eng = 6;
	int width_Math = 6;
	int width_Soci = 6;
	int width_Sci = 6;
	int width_Total = 7;
	int width_Aver = 7;
	int totalSize = 0;
	int offset_x = 1;

	int selectedMenu = -1;

	struct menu
	{
		std::string key;
		std::string name;
	};
	menu* mainMenu = nullptr;
public:

	enum EMAINMENU
	{
		EN_INSERT_NEW_STUDENT = (int)0, 
		EN_ERASE_STUDENT,
		EN_FIND_STUDENT,
		EN_SORT_STUDENT,
		EN_MAKE_DUMMY,
		EN_SAVE_FILE,
		EN_LOAD_FILE,
		EN_EXIT,
		SIZE
	};

private:
	void printOffset();

public:
	UI() : studentManager(nullptr) { initialize(); };
	UI(studentMgr* _stuMgr) : studentManager(_stuMgr) { initialize(); };
	~UI() { studentManager = nullptr; releaseMenu(); };

	// Common
	void initialize();
	void initializeMenu();
	void releaseMenu();
	void printSingleLine();
	void printDoubleLine();
	void printTitleLine(std::string _title);
	void printTitle(std::string _title);
	void printParamList();
	void printMenuTitleLine(std::string _title);
	void printMenuLine(std::string _key, std::string _title);
	void redraw();

	// Menu
	void printMainMenu();
	void printSortMenu();

	// Data
	void printData();
	void printStudentData(student& _student);


	void findStudent();
	void sortStudent();

	// Input
	int getInputKey();
	//int getInputInt(std::string _prnt = "");
	std::string getInputName();


	void getInputStudent(student& _student);
	int getInputEraseTarget();
	
};