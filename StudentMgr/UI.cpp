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
	WriteFile(displayBuffer[bufferIdx], _string.c_str(), (DWORD)_string.length(), &dw, NULL);
}

void consoleUI::moveCurPos(int _x, int _y)
{
	COORD pos = { (SHORT)_x, (SHORT)_y};
	SetConsoleCursorPosition(displayBuffer[bufferIdx], pos);
}

//////////////////////////////////////




void UI::updateTable()
{
	vecTable.clear();
	max_page = (int)ceil(studentManager->getSize() / (double)maxSizePage);
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
	menuMain[EMENU_MAIN::EN_INSERT].name = "Insert Student";
	menuMain[EMENU_MAIN::EN_ERASE].name = "Erase Student";
	menuMain[EMENU_MAIN::EN_FIND].name = "Find Student";
	menuMain[EMENU_MAIN::EN_SORT].name = "Sort Student";
	menuMain[EMENU_MAIN::EN_MAKE_DUMMY].name = "Make Dummy Student";
	menuMain[EMENU_MAIN::EN_SAVE].name = "Save File";
	menuMain[EMENU_MAIN::EN_LOAD].name = "Load File";
	menuMain[EMENU_MAIN::EN_NEXT].name = "Next";
	menuMain[EMENU_MAIN::EN_PREV].name = "Prev";

	for (int i = 0; i < EMENU_MAIN::MENU_MAIN_SIZE; i++)
	{
		menuMain[i].x = 65;
		menuMain[i].y = 3 + i;
	}

	menuMain[EMENU_MAIN::EN_NEXT].x = 40;
	menuMain[EMENU_MAIN::EN_NEXT].y = 25;
	menuMain[EMENU_MAIN::EN_NEXT].visible = false;
	
	menuMain[EMENU_MAIN::EN_PREV].x = 20;
	menuMain[EMENU_MAIN::EN_PREV].y = 25;
	menuMain[EMENU_MAIN::EN_PREV].visible = false;
	

	// 1. Erase Menu
	menuErase = new menu[EMENU_ERASE::MENU_ERASE_SIZE];
	menuErase[EMENU_ERASE::EN_ERASE_ID].name = "Erase by ID";
	menuErase[EMENU_ERASE::EN_ERASE_NAME].name = "Erase by Name";

	// 3. Sort Menu
	menuSort = new menu[EMENU_SORT::MENU_SORT_SIZE];
	menuSort[EMENU_SORT::EN_ASCENDING_ID].name = "Sort by ID(Ascending)";
	menuSort[EMENU_SORT::EN_ASCENDING_NAME].name = "Sort by Name(Ascending)";
	menuSort[EMENU_SORT::EN_ASCENDING_AGE].name = "Sort by Age(Ascending)";
	menuSort[EMENU_SORT::EN_DECENDING_KOR].name = "Sort by Kor(Decending)";
	menuSort[EMENU_SORT::EN_DECENDING_ENG].name = "Sort by Eng(Decending)";
	menuSort[EMENU_SORT::EN_DECENDING_MATH].name = "Sort by Math(Decending)";
	menuSort[EMENU_SORT::EN_DECENDING_SOCI].name = "Sort by Soci(Decending)";
	menuSort[EMENU_SORT::EN_DECENDING_SCI].name = "Sort by Sci(Decending)";
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
	if (tableStudent != nullptr)
	{
		delete[] tableStudent;
		tableStudent = nullptr;
	}	
}

void UI::printFrame()
{
	// Title Frame
	std::string doubleLine = makeStrLine("=");
	printString(0, 0, doubleLine);
	printTitle("Student Manager");
	printString(0, 2, doubleLine);

	// Student Element List
	printStudentElementTable();
	std::string singleLine = makeStrLine("-");
	printString(0, 4, singleLine);

	// Menu Frame
	for (int i = 0; i < 26; i++)
	{
		printString(61, i, "|");
	}

	for (int i = 0; i < 26; i++)
	{
		printString(90, i, "|");
	}

	for (int i = 0; i < 28; i++)
	{
		printString(62 + i, 0, "=");
		printString(62 + i, 2, "=");
		printString(62 + i, 2 + EMENU_MAIN::MENU_MAIN_SIZE, "=");
		printString(62 + i, 4 + EMENU_MAIN::MENU_MAIN_SIZE, "=");
	}

	// Bottom Line
	std::string singleLineBottom = makeStrLine("-", 90);
	printString(0, 26, singleLineBottom);
}



//void UI::getInputStudent(student& _target)
//{
//	//printMenuTitleLine();
//	std::string name = getInputString("Name: ");
//	_target.setName(name);
//
//	int age = getInputNumber("Age: ");
//	_target.setAge(age);
//
//	int scoreKor = getInputNumber("Kor: ");
//	_target.setScore(ESUBJECT::EN_KOR, scoreKor);
//
//	int scoreEng = getInputNumber("Eng: ");
//	_target.setScore(ESUBJECT::EN_ENG, scoreEng);
//
//	int scoreMath = getInputNumber("Math: ");
//	_target.setScore(ESUBJECT::EN_MATH, scoreMath);
//
//	int scoreSoci = getInputNumber("Soci: ");
//	_target.setScore(ESUBJECT::EN_SOCI, scoreSoci);
//
//	int scoreSci = getInputNumber("Sci: ");
//	_target.setScore(ESUBJECT::EN_SCI, scoreSci);
//}

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
	int x = (width - (int)_title.length()) / 2;
	printString(x, 1, _title);
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

	
}

void UI::printMenu()
{
	printString(65, 1, "Menu");

	if (cur_page < (max_page - 1))
	{
		menuMain[EMENU_MAIN::EN_NEXT].visible = true;
	}
	else
	{
		menuMain[EMENU_MAIN::EN_NEXT].visible = false;
	}

	if (cur_page > 0)
	{
		menuMain[EMENU_MAIN::EN_PREV].visible = true;
	}
	else
	{
		menuMain[EMENU_MAIN::EN_PREV].visible = false;
	}

	for (int i = 0; i < EMENU_MAIN::MENU_MAIN_SIZE; i++)
	{
		if (menuMain[i].visible)
		{
			printString(menuMain[i].x, menuMain[i].y, menuMain[i].name);
		}
	}
}

void UI::printSubMenu()
{
	printString(65, 3 + EMENU_MAIN::MENU_MAIN_SIZE, menuMain[selectedMenu].name);	
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

void UI::moveCurMenuPos()
{
	POINT offset = { 2, 0 };
	if (currentSubMenu < 0)
	{
		if (menuMain[currentMenu].visible)
		{
			if ((currentMenu >= 0) && (currentMenu < EMENU_MAIN::MENU_MAIN_SIZE))
			{
				cursor.x = menuMain[currentMenu].x - offset.x;
				cursor.y = menuMain[currentMenu].y - offset.y;
				printString(cursor.x, cursor.y, ">"); // menu selector - cursor

			}
		}
	}
	else
	{
		if (currentSubMenu < maxSubMenu)
		{
			cursor.x = subMenuPos.x - offset.x;
			cursor.y = subMenuPos.y - offset.y + currentSubMenu;
			printString(cursor.x, cursor.y, ">"); // menu selector - cursor

		}
	}

}

DWORD __stdcall UI::displayThread(LPVOID lpParam)
{
	srand(static_cast<unsigned int>(time(NULL)));

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
		bool bChange = false;
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			// Sub Menu
			if (ui->currentSubMenu >= 0)
			{
				ui->selectedSubMenu = ui->currentSubMenu;

				if (ui->inputStrFlag)
				{
					ui->inputStrFlag = false;
					ui->inputEndFlag = true;
				}
			}

			// Main Menu
			ui->selectedMenu = ui->currentMenu;
			bChange = true;
		}
		else
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				if (ui->currentSubMenu >= 0)
				{
					ui->selectedSubMenu = -1;
					ui->currentSubMenu = -1;
					ui->selectedMenu = -1;
					ui->inputStrFlag = false;
					ui->inputNumFlag = false;
					for (int i = 0; i < ui->maxTempString; i++)
					{
						ui->tempString[i].clear();
					}

					bChange = true;
				}
				else
				{
					ui->exitThread();
					break;
				}
			}

			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				// Sub Menu Control
				if (ui->currentSubMenu != -1)
				{
					if (ui->currentSubMenu < (ui->maxSubMenu - 1))
					{
						ui->currentSubMenu++;
						ui->inputStrFlag = false;
						ui->inputNumFlag = false;
					}
					bChange = true;
				}
				// Main Menu Control
				else
				{
					if (ui->currentMenu < EMENU_MAIN::EN_LOAD)
					{
						ui->currentMenu++;
						bChange = true;
					}
				}
			}

			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				// Sub Menu Control
				if (ui->currentSubMenu > 0)
				{
					ui->currentSubMenu--;
					ui->inputStrFlag = false;
					ui->inputNumFlag = false;
					bChange = true;
				}
				// Main Menu Control
				else if(ui->currentSubMenu < 0)
				{
					if (ui->currentMenu > 0 && (ui->currentMenu < EMENU_MAIN::EN_NEXT))
					{
						ui->currentMenu--;
						bChange = true;
					}
				}
			}

			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				if (ui->currentSubMenu == -1)
				{
					if (ui->currentMenu < EMENU_MAIN::EN_NEXT)
					{
						if (ui->menuMain[EMENU_MAIN::EN_NEXT].visible)
						{
							ui->currentMenu = EMENU_MAIN::EN_NEXT;
							bChange = true;
						}
						else if (ui->menuMain[EMENU_MAIN::EN_PREV].visible)
						{
							ui->currentMenu = EMENU_MAIN::EN_PREV;
							bChange = true;
						}
					}
					else if (ui->currentMenu == EMENU_MAIN::EN_NEXT)
					{
						if (ui->menuMain[EMENU_MAIN::EN_PREV].visible)
						{
							ui->currentMenu = EMENU_MAIN::EN_PREV;
							bChange = true;
						}
					}
				}
				
				//ui->runDisplay();
			}

			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				if (ui->currentSubMenu == -1)
				{
					if (ui->currentMenu == EMENU_MAIN::EN_PREV)
					{
						if (ui->menuMain[EMENU_MAIN::EN_NEXT].visible)
						{
							ui->currentMenu = EMENU_MAIN::EN_NEXT;
							bChange = true;
						}
						else
						{
							ui->currentMenu = EMENU_MAIN::EN_INSERT;
							bChange = true;
						}
					}
					else if (ui->currentMenu == EMENU_MAIN::EN_NEXT)
					{
						ui->currentMenu = EMENU_MAIN::EN_INSERT;
						bChange = true;
					}
				}
			}

			if (ui->inputStrFlag)
			{
				if (GetAsyncKeyState(VK_BACK) & 0x8000)
				{
					if (!ui->tempString[ui->currentSubMenu].empty())
					{
						ui->tempString[ui->currentSubMenu].pop_back();
						bChange = true;
					}
				}

				for (int key = EKEY::A; key <= EKEY::Z; key++)
				{
					if (ui->tempString[ui->currentSubMenu].length() < 10)
					{
						if (GetAsyncKeyState(key) & 0x8000)
						{
							ui->tempString[ui->currentSubMenu].push_back(key);
							bChange = true;
						}
					}
				}
			}
			if (ui->inputNumFlag)
			{
				if (GetAsyncKeyState(VK_BACK) & 0x8000)
				{
					if (!ui->tempString[ui->currentSubMenu].empty())
					{
						ui->tempString[ui->currentSubMenu].pop_back();
						bChange = true;
					}
				}

				for (int key = 48; key <= 57; key++) // 47: 0 ~ 57 : 9
				{
					if (ui->tempString[ui->currentSubMenu].length() < 10)
					{
						if (GetAsyncKeyState(key) & 0x8000)
						{
							ui->tempString[ui->currentSubMenu].push_back(key);
							bChange = true;
						}
					}
				}
			}
		}

		if (bChange)
		{
			ui->runDisplay();
			Sleep(100);
		}

		//Sleep(100);
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
	printFrame();
	
	switch (selectedMenu)
	{
		case EMENU_MAIN::EN_INSERT:
		{
			student newStudent;
			//getInputStudent(newStudent);
			printSubMenu();
			insertStudent();
			updateTable();
			break;
		}
		case EMENU_MAIN::EN_ERASE:
		{
			printSubMenu();
			eraseStudent();
			updateTable();
			break;
		}
		case EMENU_MAIN::EN_FIND:
		{
			printSubMenu();
			findStudent();
			break;
		}
		case EMENU_MAIN::EN_SORT:
		{
			printSubMenu();
			sortStudent();
			updateTable();
			break;
		}
		case EMENU_MAIN::EN_MAKE_DUMMY:
		{
			studentManager->insertDummyStudent();
			selectedMenu = -1;
			updateTable();
			break;
		}
		case EMENU_MAIN::EN_SAVE:
		{
			saveFile();
			selectedMenu = -1;
			break;
		}
		case EMENU_MAIN::EN_LOAD:
		{
			printSubMenu();
			loadFile();
			updateTable();
			//selectedMenu = -1;
			break;
		}	

		case EMENU_MAIN::EN_NEXT:
		{
			if (cur_page < (max_page - 1))
			{
				cur_page++;
			}

			if (cur_page == (max_page - 1))
			{
				if (menuMain[EMENU_MAIN::EN_PREV].visible)
				{
					currentMenu = EMENU_MAIN::EN_PREV;
				}
				else
				{
					currentMenu = EMENU_MAIN::EN_INSERT;
				}
			}
			selectedMenu = -1;
			break;
		}

		case EMENU_MAIN::EN_PREV:
		{
			if(cur_page > 0)
			{
				cur_page--;
			}

			if (cur_page == 0)
			{
				if (menuMain[EMENU_MAIN::EN_NEXT].visible)
				{
					currentMenu = EMENU_MAIN::EN_NEXT;
				}
				else
				{
					currentMenu = EMENU_MAIN::EN_INSERT;
				}
			}
			selectedMenu = -1;
			break;
		}
	}
	moveCurMenuPos();

	printMenu();
	printStudentTable();
}

///////////////////////////////////////////////////////////////////
// Sub Menu
///////////////////////////////////////////////////////////////////
void UI::insertStudent()
{
	if (currentSubMenu < 0)
	{
		currentSubMenu = 0;
	}

	maxSubMenu = 8;

	if (currentSubMenu == 0)
	{
		inputStrFlag = true;
	}
	else if (currentSubMenu > 0 && currentSubMenu < maxSubMenu)
	{
		inputNumFlag = true;
	}

	printString(subMenuPos.x, subMenuPos.y, "Name: ");
	printString(subMenuPos.x + 6, subMenuPos.y, tempString[0]);

	printString(subMenuPos.x, subMenuPos.y + 1, "Age: ");
	printString(subMenuPos.x + 6, subMenuPos.y + 1, tempString[1]);

	printString(subMenuPos.x, subMenuPos.y + 2, "Kor: ");
	printString(subMenuPos.x + 6, subMenuPos.y + 2, tempString[2]);

	printString(subMenuPos.x, subMenuPos.y + 3, "Eng: ");
	printString(subMenuPos.x + 6, subMenuPos.y + 3, tempString[3]);

	printString(subMenuPos.x, subMenuPos.y + 4, "Math: ");
	printString(subMenuPos.x + 6, subMenuPos.y + 4, tempString[4]);

	printString(subMenuPos.x, subMenuPos.y + 5, "Soci: ");
	printString(subMenuPos.x + 6, subMenuPos.y + 5, tempString[5]);

	printString(subMenuPos.x, subMenuPos.y + 6, "Sci: ");
	printString(subMenuPos.x + 6, subMenuPos.y + 6, tempString[6]);
	
	printString(subMenuPos.x, subMenuPos.y + 7, "Insert");
	
	if (selectedSubMenu == 7)
	{
		selectedSubMenu = -1;
		currentSubMenu = -1;
		selectedMenu = -1;

		student newStudent;
		if (!tempString[0].empty())
		{
			newStudent.setName(tempString[0]);

			if (!tempString[1].empty())
			{
				newStudent.setAge(std::stoi(tempString[1]));
			}

			if (!tempString[2].empty())
			{
				int score = std::stoi(tempString[2]);
				score = score > 100 ? 100 : score;
				newStudent.setScore(ESUBJECT::EN_KOR, score);
			}

			if (!tempString[3].empty())
			{
				int score = std::stoi(tempString[3]);
				score = score > 100 ? 100 : score;
				newStudent.setScore(ESUBJECT::EN_ENG, score);
			}

			if (!tempString[4].empty())
			{
				int score = std::stoi(tempString[4]);
				score = score > 100 ? 100 : score;
				newStudent.setScore(ESUBJECT::EN_MATH, score);
			}

			if (!tempString[5].empty())
			{
				int score = std::stoi(tempString[5]);
				score = score > 100 ? 100 : score;
				newStudent.setScore(ESUBJECT::EN_SOCI, score);
			}

			if (!tempString[6].empty())
			{
				int score = std::stoi(tempString[6]);
				score = score > 100 ? 100 : score;
				newStudent.setScore(ESUBJECT::EN_SCI, score);
			}

			studentManager->insertStudent(newStudent);
		}

		for (int i = 0; i < maxTempString; i++)
		{
			tempString[i].clear();
		}
	}
}

void UI::eraseStudent()
{
	if (currentSubMenu < 0)
	{
		currentSubMenu = 0;
	}

	maxSubMenu = 2;

	if (currentSubMenu == 0)
	{
		inputNumFlag = true;
	}

	printString(subMenuPos.x, subMenuPos.y, "ID: ");
	printString(subMenuPos.x + 6, subMenuPos.y, tempString[0]);

	printString(subMenuPos.x, subMenuPos.y + 1, "Erase");

	if (selectedSubMenu == 1)
	{
		selectedSubMenu = -1;
		currentSubMenu = -1;
		selectedMenu = -1;

		int id = 0;
		if (!tempString[0].empty())
		{
			id = std::stoi(tempString[0]);
			studentManager->eraseStudent(id);
		}

		for (int i = 0; i < maxTempString; i++)
		{
			tempString[i].clear();
		}
	}
}

void UI::findStudent()
{
	if (currentSubMenu < 0)
	{
		currentSubMenu = 0;
	}

	maxSubMenu = 2;

	if (currentSubMenu == 0)
	{
		inputStrFlag = true;
	}

	printString(subMenuPos.x, subMenuPos.y, "Name: ");
	printString(subMenuPos.x + 6, subMenuPos.y, tempString[0]);

	printString(subMenuPos.x, subMenuPos.y + 1, "Find");

	if (selectedSubMenu == 1)
	{
		selectedSubMenu = -1;
		currentSubMenu = -1;
		selectedMenu = -1;

		if (!tempString[0].empty())
		{
			LL::List<student> findedStudent;
			studentManager->findNameAll(tempString[0], findedStudent);

			if (findedStudent.size() > 0)
			{
				int lineNum = 3;
				printString(subMenuPos.x, subMenuPos.y + 2, "Finded ID: ");
				for (auto it = findedStudent.begin(); it != findedStudent.end(); it++)
				{
					printString(subMenuPos.x, subMenuPos.y + lineNum, std::to_string((*it).getID()));
					lineNum++;
				}
			}
			else
			{
				printString(subMenuPos.x, subMenuPos.y + 2, "Failed Find!");
			}
		}
		else
		{
			printString(subMenuPos.x, subMenuPos.y + 2, "Failed Find!");
		}

		for (int i = 0; i < maxTempString; i++)
		{
			tempString[i].clear();
		}
	}
}

void UI::sortStudent()
{
	if (currentSubMenu < 0)
	{
		currentSubMenu = 0;
	}

	maxSubMenu = EMENU_SORT::MENU_SORT_SIZE;

	for (int i = 0; i < EMENU_SORT::MENU_SORT_SIZE; i++)
	{
		printString(subMenuPos.x, subMenuPos.y + i, menuSort[i].name);
	}

	if (selectedSubMenu >= 0)
	{
		switch (selectedSubMenu)
		{
		case EMENU_SORT::EN_ASCENDING_ID:
			studentManager->sortID();
			break;
		case EMENU_SORT::EN_ASCENDING_NAME:
			studentManager->sortName();
			break;
		case EMENU_SORT::EN_ASCENDING_AGE:
			studentManager->sortAge();
			break;
		case EMENU_SORT::EN_DECENDING_KOR:
			studentManager->sortScore(ESUBJECT::EN_KOR);
			break;
		case EMENU_SORT::EN_DECENDING_ENG:
			studentManager->sortScore(ESUBJECT::EN_ENG);
			break;
		case EMENU_SORT::EN_DECENDING_MATH:
			studentManager->sortScore(ESUBJECT::EN_MATH);
			break;
		case EMENU_SORT::EN_DECENDING_SOCI:
			studentManager->sortScore(ESUBJECT::EN_SOCI);
			break;
		case EMENU_SORT::EN_DECENDING_SCI:
			studentManager->sortScore(ESUBJECT::EN_SCI);
			break;
		}

		selectedSubMenu = -1;
		currentSubMenu = -1;
		selectedMenu = -1;
	}
}

void UI::saveFile()
{
	if (!studentManager->empty())
	{
		time_t curTime = time(NULL);
		struct tm t;
		localtime_s(&t, &curTime);
		std::string year = std::to_string(t.tm_year + 1900);
		std::string month = t.tm_mon + 1 < 10 ? "0" + std::to_string(t.tm_mon + 1) : std::to_string(t.tm_mon + 1);
		std::string day = t.tm_mday < 10 ? "0" + std::to_string(t.tm_mday) : std::to_string(t.tm_mday);
		std::string hour = t.tm_hour < 10 ? "0" + std::to_string(t.tm_hour) : std::to_string(t.tm_hour);
		std::string min = t.tm_min < 10 ? "0" + std::to_string(t.tm_min) : std::to_string(t.tm_min);

		std::string name = "Save_"
			+ year
			+ month
			+ day + "_"
			+ hour
			+ min
			+ ".csv";
		studentManager->saveFile(name);
	}
}

void UI::loadFile()
{
	studentManager->findFile();
	std::vector<std::string> fileList = studentManager->getFileList();
	if (!fileList.empty())
	{
		size_t max = fileList.size() > 10 ? 10 : fileList.size();
		for (size_t cnt = 0; cnt < max; cnt++)
		{
			printString(subMenuPos.x, subMenuPos.y + cnt, fileList[cnt]);
		}

		maxSubMenu = max;

		if (currentSubMenu < 0)
		{
			currentSubMenu = 0;
		}

		if (selectedSubMenu >= 0)
		{
			studentManager->loadFile(fileList[selectedSubMenu]);
			selectedSubMenu = -1;
			currentSubMenu = -1;
			selectedMenu = -1;
		}
	}

	

}
