#include "UI.h"

consoleUI::consoleUI()
{
	initializeBuffer();
}

consoleUI::~consoleUI()
{
	releaseBuffer();
}

void consoleUI::initializeBuffer()
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

void consoleUI::releaseBuffer()
{
	CloseHandle(displayBuffer[0]);
	CloseHandle(displayBuffer[1]);
}

void consoleUI::bufferSwitching()
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

void consoleUI::displayClear()
{
	COORD pos = { 0, 0 };
	DWORD dw;

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);
	int width = bufferInfo.dwSize.X;
	int height = bufferInfo.dwSize.Y;
	FillConsoleOutputCharacter(displayBuffer[bufferIdx], ' ', width * height, pos, &dw);
}

void consoleUI::printString(int _x, int _y, std::string _string)
{
	DWORD dw;
	moveCurPos(_x, _y);
	WriteFile(displayBuffer[bufferIdx], _string.c_str(), _string.length(), &dw, NULL);
}

void consoleUI::moveCurPos(int _x, int _y)
{
	COORD pos = { _x, _y };
	if (SetConsoleCursorPosition(displayBuffer[bufferIdx], pos));
}




void UI::updateTable()
{
	vecTable.clear();
	max_page = ceil(studentManager->getSize() / maxSizePage);
	cur_page = max_page - 1;
	for (auto it = studentManager->begin(); it != studentManager->end(); it++)
	{
		std::vector<std::string> vecStudent;
		vecStudent.push_back(std::to_string((*it).getID()));
		vecStudent.push_back((*it).getName());
		vecStudent.push_back(std::to_string((*it).getAge()));
		vecStudent.push_back(std::to_string((*it).getScore(ESUBJECT::EN_KOR)));
		vecStudent.push_back(std::to_string((*it).getScore(ESUBJECT::EN_ENG)));
		vecStudent.push_back(std::to_string((*it).getScore(ESUBJECT::EN_MATH)));
		vecStudent.push_back(std::to_string((*it).getScore(ESUBJECT::EN_SOCI)));
		vecStudent.push_back(std::to_string((*it).getScore(ESUBJECT::EN_SCI)));
		vecStudent.push_back(std::to_string((*it).getTotalScore()));
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << (*it).getAverageScore();
		vecStudent.push_back(stream.str());

		vecTable.push_back(vecStudent);
	}
}

void UI::initialize()
{
	initializeMenu();
	initializeTable();

	// console resizing.
	/*HWND console = GetConsoleWindow();
	RECT consoleRect;
	GetWindowRect(console, &consoleRect);
	MoveWindow(console, consoleRect.left, consoleRect.top, 500, 600, true);*/

	runEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("run_display"));
	exitEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("exit_thread"));

	threadHandle[0] = CreateThread(NULL, 0, displayThread, this, 0, 0);
	threadHandle[1] = CreateThread(NULL, 0, keyboardThread, this, 0, 0);	
}

void UI::initializeMenu()
{
	// Main Menu
	menuMain = new menu[EMENU_MAIN::MENU_MAIN_SIZE];
	menuMain[EMENU_MAIN::EN_INSERT_NEW_STUDENT].name = "Insert Student";
	menuMain[EMENU_MAIN::EN_ERASE_STUDENT].name = "Erase Student";
	menuMain[EMENU_MAIN::EN_FIND_STUDENT].name = "Find Student";
	menuMain[EMENU_MAIN::EN_SORT_STUDENT].name = "Sort Student";
	menuMain[EMENU_MAIN::EN_MAKE_DUMMY].name = "Make Dummy Student";
	menuMain[EMENU_MAIN::EN_SAVE_FILE].name = "Save File";
	menuMain[EMENU_MAIN::EN_LOAD_FILE].name = "Load File";

	// 1. Erase Menu
	menuErase = new menu[EMENU_ERASE::MENU_ERASE_SIZE];
	menuErase[EMENU_ERASE::EN_ERASE_ID].name = "Erase by ID";
	menuErase[EMENU_ERASE::EN_ERASE_NAME].name = "Erase by Name";

	// 3. Sort Menu
	menuSort = new menu[EMENU_SORT::MENU_SORT_SIZE];
	menuSort[EMENU_SORT::EN_SORT_ID].name = "Sort by ID";
	menuSort[EMENU_SORT::EN_SORT_NAME].name = "Sort by Name";
	menuSort[EMENU_SORT::EN_SORT_AGE].name = "Sort by Age";
	menuSort[EMENU_SORT::EN_SORT_SCORE].name = "Sort by Score";
	
	// 3. Sort Menu - Sort Type
	menuSortType = new menu[EMENU_SORT_TYPE::SORT_TYPE_SIZE];
	menuSortType[EMENU_SORT_TYPE::EN_ASCENDING].name = "Ascending";
	menuSortType[EMENU_SORT_TYPE::EN_DECENDING].name = "Decending";

	// 3. Sort Menu - Sort Subject
	menuSortSubject = new menu[EMENU_SORT_SUBJECT::SUBJECT_SIZE];
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_KOR].name = "Korean";
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_ENG].name = "English";
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_MATH].name = "Math";
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_SOCI].name = "Society";
	menuSortSubject[EMENU_SORT_SUBJECT::EN_SUB_SCI].name = "Science";
}

void UI::initializeTable()
{
	tableStudent = new tableInfo[ESTUDENT_TABLE::STUDENT_ELEMENTS_SIZE];

	tableStudent[ESTUDENT_TABLE::EN_ID].width = 5;
	tableStudent[ESTUDENT_TABLE::EN_ID].x = 1;
	tableStudent[ESTUDENT_TABLE::EN_ID].name = "ID";

	tableStudent[ESTUDENT_TABLE::EN_NAME].width = 7;
	tableStudent[ESTUDENT_TABLE::EN_NAME].x = tableStudent[ESTUDENT_TABLE::EN_ID].x + tableStudent[ESTUDENT_TABLE::EN_ID].width;
	tableStudent[ESTUDENT_TABLE::EN_NAME].name = "Name";

	tableStudent[ESTUDENT_TABLE::EN_AGE].width = 6;
	tableStudent[ESTUDENT_TABLE::EN_AGE].x = tableStudent[ESTUDENT_TABLE::EN_NAME].x + tableStudent[ESTUDENT_TABLE::EN_NAME].width;
	tableStudent[ESTUDENT_TABLE::EN_AGE].name = "Age";

	tableStudent[ESTUDENT_TABLE::EN_KOR].width = 6;
	tableStudent[ESTUDENT_TABLE::EN_KOR].x = tableStudent[ESTUDENT_TABLE::EN_AGE].x + tableStudent[ESTUDENT_TABLE::EN_AGE].width;
	tableStudent[ESTUDENT_TABLE::EN_KOR].name = "Kor";

	tableStudent[ESTUDENT_TABLE::EN_ENG].width = 6;
	tableStudent[ESTUDENT_TABLE::EN_ENG].x = tableStudent[ESTUDENT_TABLE::EN_KOR].x + tableStudent[ESTUDENT_TABLE::EN_KOR].width;
	tableStudent[ESTUDENT_TABLE::EN_ENG].name = "Eng";

	tableStudent[ESTUDENT_TABLE::EN_MATH].width = 6;
	tableStudent[ESTUDENT_TABLE::EN_MATH].x = tableStudent[ESTUDENT_TABLE::EN_ENG].x + tableStudent[ESTUDENT_TABLE::EN_ENG].width;
	tableStudent[ESTUDENT_TABLE::EN_MATH].name = "Math";

	tableStudent[ESTUDENT_TABLE::EN_SOCI].width = 6;
	tableStudent[ESTUDENT_TABLE::EN_SOCI].x = tableStudent[ESTUDENT_TABLE::EN_MATH].x + tableStudent[ESTUDENT_TABLE::EN_MATH].width;
	tableStudent[ESTUDENT_TABLE::EN_SOCI].name = "Soci";

	tableStudent[ESTUDENT_TABLE::EN_SCI].width = 6;
	tableStudent[ESTUDENT_TABLE::EN_SCI].x = tableStudent[ESTUDENT_TABLE::EN_SOCI].x + tableStudent[ESTUDENT_TABLE::EN_SOCI].width;
	tableStudent[ESTUDENT_TABLE::EN_SCI].name = "Sci";

	tableStudent[ESTUDENT_TABLE::EN_TOTAL].width = 7;
	tableStudent[ESTUDENT_TABLE::EN_TOTAL].x = tableStudent[ESTUDENT_TABLE::EN_SCI].x + tableStudent[ESTUDENT_TABLE::EN_SCI].width;
	tableStudent[ESTUDENT_TABLE::EN_TOTAL].name = "Total";

	tableStudent[ESTUDENT_TABLE::EN_AVER].width = 7;
	tableStudent[ESTUDENT_TABLE::EN_AVER].x = tableStudent[ESTUDENT_TABLE::EN_TOTAL].x + tableStudent[ESTUDENT_TABLE::EN_TOTAL].width;
	tableStudent[ESTUDENT_TABLE::EN_AVER].name = "Aver";
}

void UI::release()
{
	if (menuMain != nullptr)
	{
		delete[] menuMain;
		menuMain = nullptr;
	}
	if (menuErase != nullptr)
	{
		delete[] menuErase;
		menuErase = nullptr;
	}
	if (menuSort != nullptr)
	{
		delete[] menuSort;
		menuSort = nullptr;
	}
	if (menuSortType != nullptr)
	{
		delete[] menuSortType;
		menuSortType = nullptr;
	}
	if (menuSortSubject != nullptr)
	{
		delete[] menuSortSubject;
		menuSortSubject = nullptr;
	}
	if (tableStudent != nullptr)
	{
		delete[] tableStudent;
		tableStudent = nullptr;
	}	
}

std::string UI::getInputString(std::string _print)
{
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

void UI::makeDummyData()
{
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

void UI::printTitle(std::string _title)
{
	std::string doubleLine = makeStrLine("=");
	printString(0, 0, doubleLine);

	int x = (width - _title.length()) / 2;
	printString(x, 1, _title);
	printString(0, 2, doubleLine);
}

void UI::printStudentElementTable()
{
	int x = tableStudentPos.x;
	for (int i = 0; i < ESTUDENT_TABLE::STUDENT_ELEMENTS_SIZE; i++)
	{
		printString(x, 3, tableStudent[i].name);
		x += tableStudent[i].width;
	}
	//tableStudentPos.y++;

	std::string singleLine = makeStrLine("-");
	printString(0, 4, singleLine);
	std::string singleLineBottom = makeStrLine("-", 86);
	printString(0, 26, singleLineBottom);
}

void UI::printMenu()
{
	for (int i = 0; i < 26; i++)
	{
		printString(60, i, "|");
	}

	for (int i = 0; i < 26; i++)
	{
		printString(86, i, "|");
	}

	for (int i = 0; i < 25; i++)
	{
		printString(61 + i, 0, "=");
		printString(61 + i, 2, "=");
	}

	printString(62, 1, "Menu");
	for (int i = 0; i < EMENU_MAIN::MENU_MAIN_SIZE; i++)
	{
		printString(65, i +3, menuMain[i].name);
	}



	if (cur_page < (max_page - 1))
	{
		// next page
		printString(65, EMENU_MAIN::MENU_MAIN_SIZE + 3, "Next");
	}
	if (cur_page > 0)
	{
		// prev page
		printString(65, EMENU_MAIN::MENU_MAIN_SIZE + 4, "Prev");
	}
}

void UI::printStudentData(student& _student)
{
	printString(tableStudent[ESTUDENT_TABLE::EN_ID].x, tableStudentPos.y, std::to_string(_student.getID()));
	printString(tableStudent[ESTUDENT_TABLE::EN_NAME].x, tableStudentPos.y, _student.getName());
	printString(tableStudent[ESTUDENT_TABLE::EN_AGE].x, tableStudentPos.y, std::to_string(_student.getAge()));
	printString(tableStudent[ESTUDENT_TABLE::EN_KOR].x, tableStudentPos.y, std::to_string(_student.getScore(ESUBJECT::EN_KOR)));
	printString(tableStudent[ESTUDENT_TABLE::EN_ENG].x, tableStudentPos.y, std::to_string(_student.getScore(ESUBJECT::EN_ENG)));
	printString(tableStudent[ESTUDENT_TABLE::EN_MATH].x, tableStudentPos.y, std::to_string(_student.getScore(ESUBJECT::EN_MATH)));
	printString(tableStudent[ESTUDENT_TABLE::EN_SOCI].x, tableStudentPos.y, std::to_string(_student.getScore(ESUBJECT::EN_SOCI)));
	printString(tableStudent[ESTUDENT_TABLE::EN_SCI].x, tableStudentPos.y, std::to_string(_student.getScore(ESUBJECT::EN_SCI)));
	printString(tableStudent[ESTUDENT_TABLE::EN_TOTAL].x, tableStudentPos.y, std::to_string(_student.getTotalScore()));

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << _student.getAverageScore();
	std::string aver = stream.str();
	printString(tableStudent[ESTUDENT_TABLE::EN_AVER].x, tableStudentPos.y, aver);
}

void UI::printStudentTable()
{
	tableStudentPos.y = 5;
	if (false)
	{
		for (auto it = studentManager->begin(); it != studentManager->end(); it++)
		{
			printStudentData(*it);
			tableStudentPos.y++;
		}
	}
	else
	{
		//size_t studentSize = vecTable.size();

		size_t startIdx = vecTable.size() != 0 ? (cur_page * maxSizePage) : 0;
		size_t endIdx = vecTable.size();
		if (vecTable.size() > ((cur_page + 1) * maxSizePage))
		{
			endIdx = ((cur_page + 1) * maxSizePage);
		}
		for (size_t cnt = startIdx; cnt < endIdx; cnt++)
		{
			printString(tableStudent[ESTUDENT_TABLE::EN_ID].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_ID]);
			printString(tableStudent[ESTUDENT_TABLE::EN_NAME].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_NAME]);
			printString(tableStudent[ESTUDENT_TABLE::EN_AGE].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_AGE]);
			printString(tableStudent[ESTUDENT_TABLE::EN_KOR].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_KOR]);
			printString(tableStudent[ESTUDENT_TABLE::EN_ENG].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_ENG]);
			printString(tableStudent[ESTUDENT_TABLE::EN_MATH].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_MATH]);
			printString(tableStudent[ESTUDENT_TABLE::EN_SOCI].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_SOCI]);
			printString(tableStudent[ESTUDENT_TABLE::EN_SCI].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_SCI]);
			printString(tableStudent[ESTUDENT_TABLE::EN_TOTAL].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_TOTAL]);
			printString(tableStudent[ESTUDENT_TABLE::EN_AVER].x, tableStudentPos.y, vecTable[cnt][ESTUDENT_TABLE::EN_AVER]);
			tableStudentPos.y++;
		}
	}
}





DWORD __stdcall UI::displayThread(LPVOID lpParam)
{
	UI* ui = (UI*)lpParam;
	if (ui == nullptr)
	{
		return -1;
	}
	while (1)
	{
		DWORD dw = WaitForSingleObject(ui->exitEvent, 1);
		if (dw == WAIT_OBJECT_0)
		{
			break;
		}

		WaitForSingleObject(ui->runEvent, INFINITE);
		ui->displayClear();
		ui->display();
		ui->bufferSwitching();
		ResetEvent(ui->runEvent);
	}
	return 0;
}

DWORD __stdcall UI::keyboardThread(LPVOID lpParam)
{
	UI* ui = (UI*)lpParam;
	if (ui == nullptr)
	{
		return -1;
	}

	while (1)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			ui->selectedMenu = ui->menuCurPos_y - 3;

			ui->runDisplay();
		}
		else
		{
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				ui->exitThread();
				break;
			}

			if (GetAsyncKeyState(VK_DOWN))
			{
				if (ui->menuCurPos_y < 11)
				{
					ui->menuCurPos_y++;
				}
				ui->runDisplay();
			}

			if (GetAsyncKeyState(VK_UP))
			{
				if (ui->menuCurPos_y > 3)
				{
					ui->menuCurPos_y--;
				}
				ui->runDisplay();
			}
		}

		Sleep(100);
	}


	return 0;

}

void UI::runDisplay()
{
	SetEvent(runEvent);
}

void UI::stopDisplay()
{
	ResetEvent(runEvent);
}

void UI::exitThread()
{
	SetEvent(exitEvent);
}

HANDLE UI::getExitThread()
{
	return exitEvent;
}

void UI::display()
{
	printTitle("Student Manager");
	printStudentElementTable();
	printMenu();
	printString(menuCurPos_x, menuCurPos_y, ">"); // menu selector - cursor


	switch (selectedMenu)
	{
	case EMENU_MAIN::EN_INSERT_NEW_STUDENT:
	{
		updateTable();
		break;
	}
	case EMENU_MAIN::EN_ERASE_STUDENT:
	{
		updateTable();
		break;
	}
	case EMENU_MAIN::EN_FIND_STUDENT:
	{
		break;
	}
	case EMENU_MAIN::EN_SORT_STUDENT:
	{
		updateTable();
		break;
	}
	case EMENU_MAIN::EN_MAKE_DUMMY:
	{
		makeDummyData();
		selectedMenu = -1;
		updateTable();
		break;
	}
	case EMENU_MAIN::EN_SAVE_FILE:
	{
		break;
	}
	case EMENU_MAIN::EN_LOAD_FILE:
	{
		updateTable();
		break;
	}	

	case 7:
	{
		cur_page++;
		break;
	}

	case 8:
	{
		cur_page--;
		break;
	}
	}
	printStudentTable();
}