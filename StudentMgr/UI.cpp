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

	totalSize = width_ID + width_Name + width_Age + width_Kor + width_Eng + width_Math + width_Soci + width_Sci + width_Total + width_Aver;

	initializeMenu();
}

void UI::initializeMenu()
{
	mainMenu = new menu[EMAINMENU::SIZE];
	mainMenu[EMAINMENU::EN_INSERT_NEW_STUDENT].key = std::to_string(EMAINMENU::EN_INSERT_NEW_STUDENT);
	mainMenu[EMAINMENU::EN_INSERT_NEW_STUDENT].name = "Insert Student";

	mainMenu[EMAINMENU::EN_ERASE_STUDENT].key = std::to_string(EMAINMENU::EN_ERASE_STUDENT);
	mainMenu[EMAINMENU::EN_ERASE_STUDENT].name = "Erase Student";

	mainMenu[EMAINMENU::EN_FIND_STUDENT].key = std::to_string(EMAINMENU::EN_FIND_STUDENT);
	mainMenu[EMAINMENU::EN_FIND_STUDENT].name = "Find Student";

	mainMenu[EMAINMENU::EN_SORT_STUDENT].key = std::to_string(EMAINMENU::EN_SORT_STUDENT);
	mainMenu[EMAINMENU::EN_SORT_STUDENT].name = "Sort Student";

	mainMenu[EMAINMENU::EN_MAKE_DUMMY].key = std::to_string(EMAINMENU::EN_MAKE_DUMMY);
	mainMenu[EMAINMENU::EN_MAKE_DUMMY].name = "Make Dummy Student";

	mainMenu[EMAINMENU::EN_SAVE_FILE].key = std::to_string(EMAINMENU::EN_SAVE_FILE);
	mainMenu[EMAINMENU::EN_SAVE_FILE].name = "Save File";

	mainMenu[EMAINMENU::EN_LOAD_FILE].key = std::to_string(EMAINMENU::EN_LOAD_FILE);
	mainMenu[EMAINMENU::EN_LOAD_FILE].name = "Load File";

	mainMenu[EMAINMENU::EN_EXIT].key = std::to_string(EMAINMENU::EN_EXIT);
	mainMenu[EMAINMENU::EN_EXIT].name = "Exit";
}

void UI::releaseMenu()
{
	delete[] mainMenu;
}

void UI::printSingleLine()
{
	printOffset();
	for (int i = 0; i < totalSize; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
}

void UI::printDoubleLine()
{
	printOffset();
	for (int i = 0; i < totalSize; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;
}

void UI::printOffset()
{
	for (int i = 0; i < offset_x; i++)
	{
		std::cout << " ";
	}
}

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

void UI::printTitle(std::string _title)
{
	printDoubleLine();
	printTitleLine(_title);
	printDoubleLine();
}

void UI::printParamList()
{
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
}

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
		case EMAINMENU::EN_INSERT_NEW_STUDENT:
		{		
			printDoubleLine();
			printMenuTitleLine(mainMenu[EMAINMENU::EN_INSERT_NEW_STUDENT].name);
			printDoubleLine();
			break;
		}
		case EMAINMENU::EN_ERASE_STUDENT:
		{
			printDoubleLine();
			printMenuTitleLine(mainMenu[EMAINMENU::EN_ERASE_STUDENT].name);
			printDoubleLine();
			break;
		}
		case EMAINMENU::EN_FIND_STUDENT:
		{
			printDoubleLine();
			printMenuTitleLine(mainMenu[EMAINMENU::EN_FIND_STUDENT].name);
			printDoubleLine();
			break;
		}
		case EMAINMENU::EN_SORT_STUDENT:
		{
			printDoubleLine();
			printMenuTitleLine(mainMenu[EMAINMENU::EN_SORT_STUDENT].name);
			printDoubleLine();
			break;
		}
		case EMAINMENU::EN_MAKE_DUMMY:
		{
			printDoubleLine();
			printMenuTitleLine(mainMenu[EMAINMENU::EN_MAKE_DUMMY].name);
			printDoubleLine();
			break;
		}
		case EMAINMENU::EN_SAVE_FILE:
		{
			printDoubleLine();
			printMenuTitleLine(mainMenu[EMAINMENU::EN_SAVE_FILE].name);
			printDoubleLine();
			break;
		}
		case EMAINMENU::EN_LOAD_FILE:
		{
			printDoubleLine();
			printMenuTitleLine(mainMenu[EMAINMENU::EN_LOAD_FILE].name);
			printDoubleLine();
			break;
		}
		default:
			printMainMenu();
			break;
	}

}

void UI::printData()
{
	printParamList();
	printSingleLine();

	if (studentManager != nullptr)
	{
		if (studentManager->getSize() > 0)
		{
			for (auto it = studentManager->begin(); it != studentManager->end(); it++)
			{
				printStudentData(*it);
			}
		}
		else
		{
			std::cout << std::endl;
		}
	}
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

void UI::printMainMenu()
{
	printDoubleLine();
	printMenuTitleLine("Menu");
	printDoubleLine();
	for (int i = 0; i < EMAINMENU::SIZE; i++)
	{
		printMenuLine(mainMenu[i].key, mainMenu[i].name);
	}
	printDoubleLine();
}

void UI::printSortMenu()
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

void UI::findStudent()
{
	printDoubleLine();
	printMenuTitleLine("Find Student");
	printDoubleLine();
	std::cout << " name: ";
	std::string name;
	std::cin >> name;
	auto it = studentManager->findName(name);
	if (it != nullptr)
	{
		
	}
	else
	{
		std::cout << " Can't find name [" << name << "]" << std::endl;
		std::cout << " Please retry again." << std::endl;
	}
}

void UI::sortStudent()
{
	
}


std::string UI::getInputName()
{
	printDoubleLine();
	printMenuTitleLine("Find Student");
	printDoubleLine();
	std::cout << " name: ";
	std::string name;
	std::cin >> name;
	return name;
}

int UI::getInputEraseTarget()
{
	printDoubleLine();
	printMenuTitleLine("Erase Student");
	printDoubleLine();

	std::cout << " target ID: ";
	int id;
	std::cin >> id;

	return id;
}

int UI::getInputKey()
{
	int key = _getch();
	return key;
}

void UI::getInputStudent(student& _target)
{
	std::cout << " Name: ";
	std::string name;
	std::cin >> name;
	_target.setName(name);

	std::cout << " Age: ";
	int age;
	std::cin >> age;
	_target.setAge(age);

	std::cout << " Kor: ";
	int scoreKor;
	std::cin >> scoreKor;
	_target.setScore(ESUBJECT::EN_KOR, scoreKor);

	std::cout << " Eng: ";
	int scoreEng;
	std::cin >> scoreEng;
	_target.setScore(ESUBJECT::EN_ENG, scoreEng);

	std::cout << " Math: ";
	int scoreMath;
	std::cin >> scoreMath;
	_target.setScore(ESUBJECT::EN_MATH, scoreMath);

	std::cout << " Soci: ";
	int scoreSoci;
	std::cin >> scoreSoci;
	_target.setScore(ESUBJECT::EN_SOCI, scoreSoci);

	std::cout << " Sci: ";
	int scoreSci;
	std::cin >> scoreSci;
	_target.setScore(ESUBJECT::EN_SCI, scoreSci);
}