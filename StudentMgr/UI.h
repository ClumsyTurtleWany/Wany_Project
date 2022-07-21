#pragma once
#include <iostream>
#include <iomanip> // std::cout << std::setw << std::left...
#include <conio.h> // system("cls")
#include <Windows.h>
#include "StudentMgr.h"

#define NUM_KEY		(int)48 // ascii num 0 == 48
#define ENTER_KEY	(int)13 // ascii enter == 13
#define ESC_KEY		(int)27 // ascii escape == 27

//static HANDLE displayBuffer[2];
//static int bufferIdx = 0;

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

class UI
{
private:
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

	menu* menuMain = nullptr;
	menu* menuErase = nullptr;
	menu* menuSort = nullptr;
	menu* menuSortType = nullptr;
	menu* menuSortSubject = nullptr;

public:

	enum EMENU_MAIN
	{
		EN_INSERT_NEW_STUDENT = (int)0,
		EN_ERASE_STUDENT,
		EN_FIND_STUDENT,
		EN_SORT_STUDENT,
		EN_MAKE_DUMMY,
		EN_SAVE_FILE,
		EN_LOAD_FILE,
		EN_EXIT,
		MENU_MAIN_SIZE
	};

	enum EMENU_ERASE
	{
		EN_ERASE_ID = (int)0,
		EN_ERASE_NAME,
		MENU_ERASE_SIZE
	};

	enum EMENU_SORT
	{
		EN_SORT_ID = (int)0,
		EN_SORT_NAME,
		EN_SORT_AGE,
		EN_SORT_SCORE,		
		MENU_SORT_SIZE
	};

	enum EMENU_SORT_TYPE
	{
		EN_ASCENDING = (int)0,
		EN_DECENDING,
		SORT_TYPE_SIZE
	};

	enum EMENU_SORT_SUBJECT
	{
		EN_SUB_KOR = (int)0,
		EN_SUB_ENG,
		EN_SUB_MATH,
		EN_SUB_SOCI,
		EN_SUB_SCI,
		SUBJECT_SIZE
	};

	enum EELEMENT_STUDENT
	{
		EN_ID = (int)0,
		EN_NAME,
		EN_AGE,
		EN_KOR,
		EN_ENG,
		EN_MATH,
		EN_SOCI,
		EN_SCI,
		EN_TOTAL,
		EN_AVER,
		STUDENT_ELEMENTS_SIZE
	};

private:
	void printOffset();

public:
	UI() { initialize(); };
	~UI() { release(); };

	// Common
	void initialize();
	void initializeMenu();
	void release();

	// Display
	void printSingleLine();
	void printDoubleLine();
	void printTitleLine(std::string _title);
	void printTitle(std::string _title);
	void printStudentElementList();
	void printMenuTitleLine(std::string _title);
	void printMenuLine(std::string _key, std::string _title);
	void redraw();

	// Display - Menu
	void printMenuMain();
	void printMenuSort();

	// 0. Insert
	void getInputStudent(student& _student);

	// 1. Erase
	void printEraseMenu();
	
	// 2. Find
	void printFindeStudentMenu();
	

	// 3. Sort
	void sortStudent();
	
	// 4. Dummy
	
	// 5. Save
	
	// 6. Load


	// Data
	void printData();
	void printStudentData(student& _student);

	// Input
	int getInputKey();
	int getInputNumber(std::string _print = "");
	std::string getInputString(std::string _print = "");

	
	//////////////////////////////////////////////////////////
	// win api for console UI - double buffer
	private:
		HANDLE displayBuffer[2];
		int bufferIdx = 0;
		int width = 70;
		int studentElementListPos_y = 4;

	public:
		void initializeBuffer();
		void releaseBuffer();
		void bufferSwitching();
		void displayClear();
		void printString(int _x, int _y, std::string _string);
		void moveCurPos(int _x, int _y);

		std::string makeStrLine(std::string _string, int _length = 0);
		
		void printTitle2(std::string _title);
		void printStudentElementList2();

};