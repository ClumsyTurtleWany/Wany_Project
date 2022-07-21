#include "main.h"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	Engine* mainEngine = new Engine;

	//std::thread keyThread(keyInputThread, mainEngine);
	//keyThread.join();
	
	//std::thread keyThread(testThread);
	//keyThread.join();

	UI* mainUI = mainEngine->getUI();
	studentMgr* studentManager = mainEngine->getManager();
	
	int x = 0;
	int y = 0;

	int selectedMenu = 0;

	while (1)
	{
		mainUI->displayClear();

		if (selectedMenu == 0)
		{
			/*mainUI->printString(5, 0, "menu1");
			mainUI->printString(5, 1, "menu2");
			mainUI->printString(5, 2, "menu3");
			mainUI->printString(5, 3, "menu4");
			mainUI->printString(5, 4, "menu5");*/
			mainUI->printTitle2("student Manager");
			mainUI->printStudentElementList2();
		}
		else if (selectedMenu == 1)
		{
			mainUI->printString(5, 0, "sort-menu1");
			mainUI->printString(5, 1, "sort-menu2");
			mainUI->printString(5, 2, "sort-menu3");
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			selectedMenu = y;
		}
		else
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (y < 4)
				{
					y++;
				}
			}

			if (GetAsyncKeyState(VK_UP))
			{
				if (y > 0)
				{
					y--;
				}
			}
		}

		mainUI->printString(x, y, ">");

		Sleep(100);

		mainUI->bufferSwitching();
	}

	delete mainEngine;
	
	return 0;
}

// create dummy data for test.
void Engine::makeDummyData()
{
	int cnt = mainUI->getInputNumber("Enter the number of students to create: ");
	for (int i = 0; i < cnt; i++)
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
}

void Engine::insertNewStudent()
{
	student newStudent;
	mainUI->getInputStudent(newStudent);
	studentManager->insertStudent(newStudent);
	mainUI->redraw();
}

void Engine::eraseStudent()
{
	mainUI->redraw();
	mainUI->printEraseMenu();
	int key = mainUI->getInputKey();
	switch (key)
	{
		case UI::EMENU_ERASE::EN_ERASE_ID:
		{
			int id = mainUI->getInputNumber("Input erase target ID: ");
			if (id != NULL)
			{
				studentManager->eraseStudent(id);
			}
			break;
		}
		case UI::EMENU_ERASE::EN_ERASE_NAME:
		{
			std::string name = mainUI->getInputString("Input erase target Name: ");
			
			LL::List<student> targetList;
			if (studentManager->findNameAll(name, targetList))
			{
				if (targetList.size() == 1)
				{
					auto it = targetList.begin();
					studentManager->eraseStudent((*it).getID());
					break;
				}
				else
				{
					mainUI->printStudentElementList();
					for (auto it = targetList.begin(); it != targetList.end(); it++)
					{
						mainUI->printStudentData(*it);
					}
					mainUI->printSingleLine();

					int id = mainUI->getInputNumber("Input erase target ID: ");
					if (id != NULL)
					{
						studentManager->eraseStudent(id);
					}
					break;
				}
			}
			else
			{

			}
		}
	}

}