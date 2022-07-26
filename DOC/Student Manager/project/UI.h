#pragma once
#include <iostream>
#include <iomanip> // std::cout << std::setw << std::left...
#include <conio.h> // system("cls")
#include <Windows.h>
#include "StudentMgr.h"
#include <thread>
#include <sstream>
#include <vector>

typedef enum EKEY
{
	A = 0x41, 
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z
};

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
	int selectedSubMenu = -1;
	int currentSubMenu = -1;
	int maxSubMenu = 0;
	int selectedMenu = -1;
	int width = 61;
	int max_page = 0;
	int maxSizePage = 20;
	int cur_page = 0;
	int currentMenu = 0;

	bool inputStrFlag = false;
	bool inputNumFlag = false;
	bool inputEndFlag = false;
	
	POINT cursor = { 0, 0 };
	POINT subMenuPos = { 65, 5 + EMENU_MAIN::MENU_MAIN_SIZE };
	POINT tableStudentPos = { 1, 4 };
	studentMgr* studentManager = nullptr;

	HANDLE threadHandle[2];
	HANDLE runEvent;
	HANDLE exitEvent;

	class menu
	{
	public:
		int x = 0;
		int y = 0;
		std::string name = "";
		bool visible = true;

		menu() {};
		menu(int _x, int _y, std::string _name, bool _visible)
			: x(_x), y(_y), name(_name), visible(_visible) {};
		~menu() {};
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
	tableInfo* tableStudent = nullptr;
	std::vector<std::vector<std::string>> vecTable;

	int maxTempString = 10;
	std::string tempString[10];
	
public:

	enum EMENU_MAIN
	{
		EN_INSERT = (int)0,
		EN_ERASE,
		EN_FIND,
		EN_SORT,
		EN_MAKE_DUMMY,
		EN_SAVE,
		EN_LOAD,
		EN_NEXT,
		EN_PREV,
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
		EN_ASCENDING_ID = (int)0,
		EN_ASCENDING_NAME,
		EN_ASCENDING_AGE,
		EN_DECENDING_KOR,
		EN_DECENDING_ENG,
		EN_DECENDING_MATH,
		EN_DECENDING_SOCI,
		EN_DECENDING_SCI,
		MENU_SORT_SIZE
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
	void display();

	std::string makeStrLine(std::string _string, int _length = 0);
	void printTitle(std::string _title);
	void printStudentElementTable();
	void printMenu();
	void printSubMenu();
	void printStudentTable();
	void printFrame();
	void printStudentData(student& _student);

	static DWORD WINAPI displayThread(LPVOID lpParam);
	static DWORD WINAPI keyboardThread(LPVOID lpParam);

	void runDisplay();
	void stopDisplay();
	void exitThread();
	HANDLE getExitThread();
	
	// cursor
	void moveCurMenuPos();


	// Menu
	// 0. Insert
	void insertStudent();
	
	// 1. Erase
	void eraseStudent();
	
	// 2. Find
	void findStudent();

	// 3. Sort
	void sortStudent();

	// 4. Dummy
	// 5. Save
	void saveFile();
	
	// 6. Load
	void loadFile();

	// Data
	void updateTable();

	// Input

};

