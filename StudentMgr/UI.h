#pragma once
#include <iostream>
#include <iomanip> // std::cout << std::setw << std::left...
#include <conio.h> // system("cls")
#include <Windows.h>
#include "StudentMgr.h"
#include <thread>
#include <sstream>
#include <vector>

#define NUM_KEY		(int)48 // ascii num 0 == 48
#define ENTER_KEY	(int)13 // ascii enter == 13
#define ESC_KEY		(int)27 // ascii escape == 27

class consoleUI
{
	//////////////////////////////////////////////////////////
	// win api for console UI - double buffer
private:
	HANDLE displayBuffer[2];
	int bufferIdx = 0;
	
public:
	consoleUI();
	virtual ~consoleUI();

	void initializeBuffer();
	void releaseBuffer();
	void bufferSwitching();
	void displayClear();
	void printString(int _x, int _y, std::string _string);
	void moveCurPos(int _x, int _y);
};

class UI : private consoleUI
{
private:
	int offset_x = 1;

	int selectedMenu = -1;

	struct menu
	{
		int x = 0;
		int y = 0;
		std::string name;
	};

	struct tableInfo
	{
		int width = 0;
		int x = 1;
		int y = 0;
		std::string name = "";
	};

	menu* menuMain = nullptr;
	menu* menuErase = nullptr;
	menu* menuSort = nullptr;
	menu* menuSortType = nullptr;
	menu* menuSortSubject = nullptr;
	tableInfo* tableStudent = nullptr;

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

	enum ESTUDENT_TABLE
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

	std::vector<std::vector<std::string>> vecTable;
	void updateTable();

public:
	UI() { initialize(); };
	UI(studentMgr* _mgr) : studentManager(_mgr) { initialize(); };
	~UI() { release(); };

	// Common
	void initialize();
	void initializeMenu();
	void initializeTable();
	void release();

	// Display
	
	
	// Display - Menu
	

	// 0. Insert
	void getInputStudent(student& _student);

	// 1. Erase
	
	// 2. Find

	// 3. Sort
	
	// 4. Dummy
	void makeDummyData();

	// 5. Save
	
	// 6. Load


	// Data
	

	// Input
	int getInputKey();
	int getInputNumber(std::string _print = "");
	std::string getInputString(std::string _print = "");

	
	//////////////////////////////////////////////////////////
	// win api for console UI - double buffer
	private:
		int width = 60;
		POINT tableStudentPos = {1, 4};
		studentMgr* studentManager = nullptr;

	public:
		
		std::string makeStrLine(std::string _string, int _length = 0);
		
		void printTitle(std::string _title);
		void printStudentElementTable();
		void printMenu();
		
		void printStudentData(student& _student);
		void printStudentTable();

		int menuCurPos_x = 63;
		int menuCurPos_y = 3;
		int max_page = 0;
		double maxSizePage = 20;
		int cur_page = 0;

		int testx = 0;
		int testy = 1;
		

		void display();


		HANDLE threadHandle[2];
		HANDLE runEvent;
		HANDLE exitEvent;
		static DWORD WINAPI displayThread(LPVOID lpParam);
		static DWORD WINAPI keyboardThread(LPVOID lpParam);

		void runDisplay();
		void stopDisplay();
		void exitThread();
		HANDLE getExitThread();
};