#include "UI.h"

void UI::initialize()
{
	width_ID = 5;
	width_Name = 7;
	width_Age = 6;
	width_Kor = 6;
	width_Eng = 6;
	width_Math = 6;
	width_Soci = 6;
	width_Sci = 6;
	width_Total = 7;
	width_Aver = 7;
	offset_x = 1;

	totalSize = width_ID + 
				width_Name + 
				width_Age + 
				width_Kor + 
				width_Eng + 
				width_Math + 
				width_Soci + 
				width_Sci + 
				width_Total + 
				width_Aver;

	HWND console = GetConsoleWindow();
	RECT consoleRect;
	GetWindowRect(console, &consoleRect);
	MoveWindow(console, consoleRect.left, consoleRect.top, 800, 800, true);


	initializeMenu();
	initializeBuffer();
}

void UI::initializeMenu()
{
	// Main Menu
	menuMain = new menu[EMENU_MAIN::MENU_MAIN_SIZE];
	menuMain[EMENU_MAIN::EN_INSERT_NEW_STUDENT].key = std::to_string(EMENU_MAIN::EN_INSERT_NEW_STUDENT);
	menuMain[EMENU_MAIN::EN_INSERT_NEW_STUDENT].name = "Insert Student";

	menuMain[EMENU_MAIN::EN_ERASE_STUDENT].key = std::to_string(EMENU_MAIN::EN_ERASE_STUDENT);
	menuMain[EMENU_MAIN::EN_ERASE_STUDENT].name = "Erase Student";

	menuMain[EMENU_MAIN::EN_FIND_STUDENT].key = std::to_string(EMENU_MAIN::EN_FIND_STUDENT);
	menuMain[EMENU_MAIN::EN_FIND_STUDENT].name = "Find Student";

	menuMain[EMENU_MAIN::EN_SORT_STUDENT].key = std::to_string(EMENU_MAIN::EN_SORT_STUDENT);
	menuMain[EMENU_MAIN::EN_SORT_STUDENT].name = "Sort Student";

	menuMain[EMENU_MAIN::EN_MAKE_DUMMY].key = std::to_string(EMENU_MAIN::EN_MAKE_DUMMY);
	menuMain[EMENU_MAIN::EN_MAKE_DUMMY].name = "Make Dummy Student";

	menuMain[EMENU_MAIN::EN_SAVE_FILE].key = std::to_string(EMENU_MAIN::EN_SAVE_FILE);
	menuMain[EMENU_MAIN::EN_SAVE_FILE].name = "Save File";

	menuMain[EMENU_MAIN::EN_LOAD_FILE].key = std::to_string(EMENU_MAIN::EN_LOAD_FILE);
	menuMain[EMENU_MAIN::EN_LOAD_FILE].name = "Load File";

	menuMain[EMENU_MAIN::EN_EXIT].key = std::to_string(EMENU_MAIN::EN_EXIT);
	menuMain[EMENU_MAIN::EN_EXIT].name = "Exit";

	// 1. Erase Menu
	menuErase = new menu[EMENU_ERASE::MENU_ERASE_SIZE];
	menuErase[EMENU_ERASE::EN_ERASE_ID].key = std::to_string(EMENU_ERASE::EN_ERASE_ID);
	menuErase[EMENU_ERASE::EN_ERASE_ID].name = "Erase by ID";

	menuErase[EMENU_ERASE::EN_ERASE_NAME].key = std::to_string(EMENU_ERASE::EN_ERASE_NAME);
	menuErase[EMENU_ERASE::EN_ERASE_NAME].name = "Erase by ID";

	// 3. Sort Menu
	menuSort = new menu[EMENU_SORT::MENU_SORT_SIZE];
	menuSort[EMENU_SORT::EN_SORT_ID].key = std::to_string(EMENU_SORT::EN_SORT_ID);
	menuSort[EMENU_SORT::EN_SORT_ID].name = "Sort by ID";

	menuSort[EMENU_SORT::EN_SORT_NAME].key = std::to_string(EMENU_SORT::EN_SORT_NAME);
	menuSort[EMENU_SORT::EN_SORT_NAME].name = "Sort by Name";

	menuSort[EMENU_SORT::EN_SORT_AGE].key = std::to_string(EMENU_SORT::EN_SORT_AGE);
	menuSort[EMENU_SORT::EN_SORT_AGE].name = "Sort by Age";

	menuSort[EMENU_SORT::EN_SORT_SCORE].key = std::to_string(EMENU_SORT::EN_SORT_SCORE);
	menuSort[EMENU_SORT::EN_SORT_SCORE].name = "Sort by Score";
	
	// 3. Sort Menu - Sort Type
	menuSortType = new menu[EMENU_SORT_TYPE::SORT_TYPE_SIZE];
	menuSortType[EMENU_SORT_TYPE::EN_ASCENDING].key = std::to_string(EMENU_SORT_TYPE::EN_ASCENDING);
	menuSortType[EMENU_SORT_TYPE::EN_ASCENDING].name = "Ascending";

	menuSortType[EMENU_SORT_TYPE::EN_DECENDING].key = std::to_string(EMENU_SORT_TYPE::EN_DECENDING);
	menuSortType[EMENU_SORT_TYPE::EN_DECENDING].name = "Decending";

	// 3. Sort Menu - Sort Subject
	menuSortSubject = new menu[EMENU_SORT_SUBJECT::SUBJECT_SIZE];
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_KOR].key = std::to_string(EMENU_SORT_SUBJECT::EN_SUB_KOR);
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_KOR].name = "Korean";

	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_ENG].key = std::to_string(EMENU_SORT_SUBJECT::EN_SUB_ENG);
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_ENG].name = "English";

	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_MATH].key = std::to_string(EMENU_SORT_SUBJECT::EN_SUB_MATH);
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_MATH].name = "Math";

	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_SOCI].key = std::to_string(EMENU_SORT_SUBJECT::EN_SUB_SOCI);
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_SOCI].name = "Society";

	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_SCI].key = std::to_string(EMENU_SORT_SUBJECT::EN_SUB_SCI);
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_SCI].name = "Science";
}

void UI::release()
{
	delete[] menuMain;
	delete[] menuErase;
	delete[] menuSort;
	delete[] menuSortType;
	delete[] menuSortSubject;
	releaseBuffer();
}

// print single line.
// ex) ----------
void UI::printSingleLine()
{
	printOffset();
	for (int i = 0; i < totalSize; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
}

// print double line.
// ex) ==========
void UI::printDoubleLine()
{
	printOffset();
	for (int i = 0; i < totalSize; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;
}

// print offset space.
// ex) offset 0:  |print
// ex) offset 5:  |     print
void UI::printOffset()
{
	for (int i = 0; i < offset_x; i++)
	{
		std::cout << " ";
	}
}

// print title line.
// ex) === _title ===
void UI::printTitleLine(std::string _title)
{
	size_t titleSize = _title.size();
	size_t doubleLineSize = totalSize - titleSize - 2;
	
	printOffset();
	for (size_t cnt = 0; cnt < (doubleLineSize / 2); cnt++)
	{
		std::cout << "=";
	}
	std::cout << " ";
	std::cout << _title;
	std::cout << " ";
	for (size_t cnt = 0; cnt < (doubleLineSize / 2) + 1; cnt++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;
}

// print title.
// ex)
// =============
// === title ===
// =============
void UI::printTitle(std::string _title)
{
	printDoubleLine();
	printTitleLine(_title);
	printDoubleLine();
}

// print elements of student list.
// ex) ele1  ele2  ele3 ......
void UI::printStudentElementList()
{
	printDoubleLine();
	printOffset();
	std::cout << std::setw(width_ID) << std::right << "ID";
	std::cout << std::setw(width_Name) << std::right << "Name";
	std::cout << std::setw(width_Age) << std::right << "Age";
	std::cout << std::setw(width_Kor) << std::right << "Kor";
	std::cout << std::setw(width_Eng) << std::right << "Eng";
	std::cout << std::setw(width_Math) << std::right << "Math";
	std::cout << std::setw(width_Soci) << std::right << "Soci";
	std::cout << std::setw(width_Sci) << std::right << "Sci";
	std::cout << std::setw(width_Total) << std::right << "Total";
	std::cout << std::setw(width_Aver) << std::right << "Aver";
	std::cout << std::endl;
	printSingleLine();
}

// print title line.
// ex) === _title ===
void UI::printMenuTitleLine(std::string _title)
{
	printOffset();
	int offsetBorder = 5;
	for (int i = 0; i < offsetBorder; i++)
	{
		std::cout << "=";
	}
	std::cout << " ";

	int width = totalSize - static_cast<int>(_title.size()) - offsetBorder - 1;
	std::cout << _title;

	for (int i = 0; i < (width - offsetBorder); i++)
	{
		std::cout << " ";
	}
	for (int i = 0; i < offsetBorder; i++)
	{
		std::cout << "=";
	}

	std::cout << std::endl;
}

void UI::printMenuLine(std::string _key, std::string _title)
{
	printOffset();
	int width = totalSize - static_cast<int>(_key.size()) - static_cast<int>(_title.size()) - 3;
	std::cout << "[" << _key << "] ";
	std::cout << _title;
	for (int i = 0; i < (width - 5); i++)
	{
		std::cout << " ";
	}
	for (int i = 0; i < 5; i++)
	{
		std::cout << "=";
	}

	std::cout << std::endl;
}

void UI::redraw()
{
	system("cls");
	printTitle("Student Manager");
	printData();
	
	switch (selectedMenu)
	{
		case EMENU_MAIN::EN_INSERT_NEW_STUDENT:
		{		
			printDoubleLine();
			printMenuTitleLine(menuMain[EMENU_MAIN::EN_INSERT_NEW_STUDENT].name);
			printDoubleLine();
			break;
		}
		case EMENU_MAIN::EN_ERASE_STUDENT:
		{
			printDoubleLine();
			printMenuTitleLine(menuMain[EMENU_MAIN::EN_ERASE_STUDENT].name);
			printDoubleLine();
			break;
		}
		case EMENU_MAIN::EN_FIND_STUDENT:
		{
			printDoubleLine();
			printMenuTitleLine(menuMain[EMENU_MAIN::EN_FIND_STUDENT].name);
			printDoubleLine();
			break;
		}
		case EMENU_MAIN::EN_SORT_STUDENT:
		{
			printDoubleLine();
			printMenuTitleLine(menuMain[EMENU_MAIN::EN_SORT_STUDENT].name);
			printDoubleLine();
			break;
		}
		case EMENU_MAIN::EN_MAKE_DUMMY:
		{
			printDoubleLine();
			printMenuTitleLine(menuMain[EMENU_MAIN::EN_MAKE_DUMMY].name);
			printDoubleLine();
			break;
		}
		case EMENU_MAIN::EN_SAVE_FILE:
		{
			printDoubleLine();
			printMenuTitleLine(menuMain[EMENU_MAIN::EN_SAVE_FILE].name);
			printDoubleLine();
			break;
		}
		case EMENU_MAIN::EN_LOAD_FILE:
		{
			printDoubleLine();
			printMenuTitleLine(menuMain[EMENU_MAIN::EN_LOAD_FILE].name);
			printDoubleLine();
			break;
		}
		default:
			printMenuMain();
			break;
	}

}

void UI::printData()
{
	printStudentElementList();
	printSingleLine();
	printDoubleLine();
}


void UI::printStudentData(student& _student)
{
	printOffset();
	std::cout << std::setw(width_ID) << std::right << _student.getID();
	std::cout << std::setw(width_Name) << std::right << _student.getName();
	std::cout << std::setw(width_Age) << std::right << _student.getAge();
	std::cout << std::setw(width_Kor) << std::right << _student.getScore(ESUBJECT::EN_KOR);
	std::cout << std::setw(width_Eng) << std::right << _student.getScore(ESUBJECT::EN_ENG);
	std::cout << std::setw(width_Math) << std::right << _student.getScore(ESUBJECT::EN_MATH);
	std::cout << std::setw(width_Soci) << std::right << _student.getScore(ESUBJECT::EN_SOCI);
	std::cout << std::setw(width_Sci) << std::right << _student.getScore(ESUBJECT::EN_SCI);
	std::cout << std::setw(width_Total) << std::right << _student.getTotalScore();
	std::cout << std::setw(width_Aver) << std::right << _student.getAverageScore() << std::endl;
}

void UI::printMenuMain()
{
	printDoubleLine();
	printMenuTitleLine("Menu");
	printDoubleLine();
	for (int i = 0; i < EMENU_MAIN::MENU_MAIN_SIZE; i++)
	{
		printMenuLine(menuMain[i].key, menuMain[i].name);
	}
	printDoubleLine();
}

void UI::printMenuSort()
{
	printDoubleLine();
	printMenuTitleLine("Sort Student");
	printDoubleLine();
	/*printMenuLine("[0] Ascending Sort by ID");
	printMenuLine("[1] Decending Sort by ID");
	printMenuLine("[2] Ascending Sort by Name");
	printMenuLine("[3] Decending Sort by Name");*/
	printDoubleLine();
}

void UI::printEraseMenu()
{
	printDoubleLine();
	printMenuTitleLine("Erase Student");
	for (int i = 0; i < EMENU_ERASE::MENU_ERASE_SIZE; i++)
	{
		printMenuLine(menuSort[i].key, menuSort[i].name);
	}
	printDoubleLine();
}

void UI::printFindeStudentMenu()
{
	printDoubleLine();
	printMenuTitleLine("Find Student");
	printDoubleLine();
}

std::string UI::getInputString(std::string _print)
{
	printOffset();
	std::cout << _print;
	std::string data;
	char ch;
	while ((ch = _getch()) != ENTER_KEY)
	{
		if (ch == ESC_KEY)
		{
			data.clear();
			break;
		}

		std::cout << ch;
		data += ch;
	}

	return data;
}

// Write explain word or sentence.
// _print: cout << _print
int UI::getInputNumber(std::string _print)
{
	printOffset();
	std::cout << _print;
	std::string data;
	char ch;
	while ((ch = _getch()) != ENTER_KEY)
	{
		if (ch == ESC_KEY)
		{
			data.clear();
			break;
		}

		if ((ch >= NUM_KEY) && (ch < (NUM_KEY + 10)))
		{
			std::cout << ch;
			data += ch;
		}
	}

	if (!data.empty())
	{
		return std::stoi(data);
	}
	else
	{
		return NULL;
	}
}


void UI::sortStudent()
{

}

int UI::getInputKey()
{
	return _getch();
}

void UI::getInputStudent(student& _target)
{
	//printMenuTitleLine();
	std::string name = getInputString("Name: ");
	_target.setName(name);

	int age = getInputNumber("Age: ");
	_target.setAge(age);

	int scoreKor = getInputNumber("Kor: ");
	_target.setScore(ESUBJECT::EN_KOR, scoreKor);

	int scoreEng = getInputNumber("Eng: ");
	_target.setScore(ESUBJECT::EN_ENG, scoreEng);

	int scoreMath = getInputNumber("Math: ");
	_target.setScore(ESUBJECT::EN_MATH, scoreMath);

	int scoreSoci = getInputNumber("Soci: ");
	_target.setScore(ESUBJECT::EN_SOCI, scoreSoci);

	int scoreSci = getInputNumber("Sci: ");
	_target.setScore(ESUBJECT::EN_SCI, scoreSci);
}

void UI::initializeBuffer()
{
	CONSOLE_CURSOR_INFO cursorInfo;

	// 화면 버퍼 2개를 만든다.
	displayBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	displayBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 커서를 숨긴다.
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(displayBuffer[0], &cursorInfo);
	SetConsoleCursorInfo(displayBuffer[1], &cursorInfo);
}

void UI::releaseBuffer()
{
	CloseHandle(displayBuffer[0]);
	CloseHandle(displayBuffer[1]);
}

void UI::bufferSwitching()
{
	SetConsoleActiveScreenBuffer(displayBuffer[bufferIdx]);
	if (bufferIdx == 1)
	{
		bufferIdx = 0;
	}
	else
	{
		bufferIdx = 1;
	}
}

void UI::displayClear()
{
	COORD pos = { 0, 0 };
	DWORD dw;
	
	//CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	//GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);
	//int width = bufferInfo.dwSize.X;
	//int height = bufferInfo.dwSize.Y;
	//int width = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
	//int height = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;
	FillConsoleOutputCharacter(displayBuffer[bufferIdx], ' ', 80 * 25, pos, &dw);
	//FillConsoleOutputCharacter(displayBuffer[bufferIdx], ' ', width * height, pos, &dw);
}

void UI::printString(int _x, int _y, std::string _string)
{
	DWORD dw;
	moveCurPos(_x, _y);
	/*COORD pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);*/
	
	WriteFile(displayBuffer[bufferIdx], _string.c_str(), _string.length(), &dw, NULL);
}

void UI::moveCurPos(int _x, int _y)
{
	COORD pos = { _x, _y };
	if (SetConsoleCursorPosition(displayBuffer[bufferIdx], pos))
	{
		int a = 0;
	}
	else
	{
		int b = 0;
	}
}

std::string UI::makeStrLine(std::string _string, int _length)
{
	int length;
	if (_length == 0)
	{
		length = width;
	}
	else
	{
		length = _length;
	}
		
	std::string line;
	for (int i = 0; i < (length / _string.length()); i++)
	{
		line += _string;
	}
	return line;
}

void UI::printTitle2(std::string _title)
{
	std::string doubleLine = makeStrLine("=");
	printString(0, 0, doubleLine);

	int x = (width - _title.length()) / 2;
	printString(x, 1, _title);
	printString(0, 2, doubleLine);
}

void UI::printStudentElementList2()
{
	int pos_x = offset_x;
	printString(pos_x, studentElementListPos_y, "ID");
	printString(pos_x += width_ID, studentElementListPos_y, "Name");
	printString(pos_x += width_Name, studentElementListPos_y, "Age");
	printString(pos_x += width_Age, studentElementListPos_y, "Kor");
	printString(pos_x += width_Kor, studentElementListPos_y, "Eng");
	printString(pos_x += width_Eng, studentElementListPos_y, "Math");
	printString(pos_x += width_Math, studentElementListPos_y, "Soci");
	printString(pos_x += width_Soci, studentElementListPos_y, "Sci");
	printString(pos_x += width_Sci, studentElementListPos_y, "Total");
	printString(pos_x += width_Total, studentElementListPos_y, "Aver");
	
	std::string singleLine = makeStrLine("-");
	printString(0, studentElementListPos_y + 1, singleLine);

}


