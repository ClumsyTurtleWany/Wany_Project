#include "main.h"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	Engine* mainEngine = new Engine;

	//std::thread keyThread(keyInputThread, mainEngine);
	//keyThread.join();
	UI* mainUI = mainEngine->getUI();
	studentMgr* studentManager = mainEngine->getMgr();
	mainUI->redraw();
	while (1)
	{
		int key = mainUI->getInputKey();
		mainUI->redraw();
		switch (key)
		{
		case UI::EMAINMENU::EN_INSERT_NEW_STUDENT + NUM_KEY:
		{			
			//mainUI->redraw();
			student newStudent;
			mainUI->getInputStudent(newStudent);
			studentManager->insertStudent(newStudent);
			mainUI->redraw();
			break;
		}

		case UI::EMAINMENU::EN_ERASE_STUDENT + NUM_KEY:
		{
			mainUI->redraw();
			int id = mainUI->getInputEraseTarget();
			if (!studentManager->eraseStudent(id))
			{
				std::cout << "Can't find id(" << id << ")." << std::endl;
			}
			else
			{
				mainUI->redraw();
			}
			break;
		}

		case UI::EMAINMENU::EN_FIND_STUDENT + NUM_KEY:
			mainUI->printData();
			mainEngine->findName();
			
			break;

		case UI::EMAINMENU::EN_SORT_STUDENT + NUM_KEY:
			mainUI->printData();
			mainUI->printSortMenu();
			break;

		case UI::EMAINMENU::EN_MAKE_DUMMY + NUM_KEY:
			mainUI->printData();
			mainEngine->makeDummyData(1);
			mainUI->redraw();
			break;

		case UI::EMAINMENU::EN_SAVE_FILE + NUM_KEY:
			mainUI->printData();
			studentManager->saveFile("test2.csv");
			mainUI->redraw();
			//mainUI->redraw();
			break;

		case UI::EMAINMENU::EN_LOAD_FILE + NUM_KEY:
			mainUI->printData();
			studentManager->loadFile("test2.csv");
			mainUI->redraw();
			//mainUI->redraw();
			break;

		case UI::EMAINMENU::EN_EXIT + NUM_KEY:
			break;

		default:
			mainUI->redraw();
			break;
		}

		//mainUI->redraw();

		if (key == UI::EMAINMENU::EN_EXIT + NUM_KEY)
		{
			break;
		}
		else
		{
			//_Engine->getUI()->redraw();
		}
	}


	delete mainEngine;
	
	return 0;
}

//void keyInputThread(Engine* _Engine)
//{
//	srand(time(NULL));
//	_Engine->getUI()->redraw();
//
//	while (1)
//	{
//		int key = _getch();
//		
//		switch (key)
//		{
//			case UI::EMAINMENU::EN_INSERT_NEW_STUDENT + NUM_KEY:
//				_Engine->getUI()->printData();
//				_Engine->insertStudent();
//				break;
//
//			case UI::EMAINMENU::EN_ERASE_STUDENT + NUM_KEY:
//				_Engine->getUI()->printData();
//				_Engine->getUI()->eraseStudent();
//				break;
//
//			case UI::EMAINMENU::EN_FIND_STUDENT + NUM_KEY:
//				_Engine->getUI()->printData();
//				_Engine->findName();
//				break;
//
//			case UI::EMAINMENU::EN_SORT_STUDENT + NUM_KEY:
//				_Engine->getUI()->printData();
//				_Engine->getUI()->printSortMenu();
//				break;
//
//			case UI::EMAINMENU::EN_MAKE_DUMMY + NUM_KEY:
//				_Engine->getUI()->printData();
//				_Engine->makeDummyData(1);
//				_Engine->getUI()->redraw();
//				break;
//
//			case UI::EMAINMENU::EN_EXIT:
//				break;
//
//			default:
//				_Engine->getUI()->printData();
//				_Engine->getUI()->printMainMenu();
//				break;
//		}
//
//		if (key == UI::EMAINMENU::EN_EXIT)
//		{
//			break;
//		}
//		else
//		{
//			//_Engine->getUI()->redraw();
//		}
//		
//	}
//}

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

void Engine::findName()
{
	std::cout << " ============================================================= " << std::endl;
	std::cout << "  Find Student                                           ===== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
	std::cout << " name: ";
	std::string name;
	std::cin >> name;

	std::cout << std::endl;
	std::cout << " ------------------------------------------------------------- " << std::endl;
	std::cout << std::setw(5) << std::right << "ID";
	std::cout << std::setw(7) << std::right << "Name";
	std::cout << std::setw(6) << std::right << "Age";
	std::cout << std::setw(6) << std::right << "Kor";
	std::cout << std::setw(6) << std::right << "Eng";
	std::cout << std::setw(6) << std::right << "Math";
	std::cout << std::setw(6) << std::right << "Soci";
	std::cout << std::setw(6) << std::right << "Sci";
	std::cout << std::setw(7) << std::right << "Total";
	std::cout << std::setw(7) << std::right << "Aver" << std::endl;
	std::cout << " ------------------------------------------------------------- " << std::endl;

	LL::List<student> findedNameList;
	studentManager->findNameAll(name, findedNameList);

	if (!findedNameList.empty())
	{
		for (auto it = findedNameList.begin(); it != findedNameList.end(); it++)
		{
			mainUI->printStudentData(*it);
		}
		std::cout << " ------------------------------------------------------------- " << std::endl;
	}
	else
	{
		std::cout << "Can't find " << name << std::endl;
	}
}
