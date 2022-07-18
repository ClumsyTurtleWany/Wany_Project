#include "main.h"

int main()
{
	Engine* mainEngine = new Engine;

	std::thread keyThread(keyInputThread, mainEngine);
	keyThread.join();

	delete mainEngine;
	
	return 0;
}

void keyInputThread(Engine* _Engine)
{
	srand(time(NULL));
	_Engine->getUI()->printData();
	_Engine->getUI()->printMainMenu();

	while (1)
	{
		int key = _getch();
		
		switch (key)
		{
			case UI::EMAINMENU::EN_INSERT_NEW_STUDENT:
				_Engine->getUI()->printData();
				_Engine->getUI()->printInsertStudent();
				break;

			case UI::EMAINMENU::EN_ERASE_STUDENT:
				_Engine->getUI()->printData();
				_Engine->getUI()->eraseStudent();
				break;

			case UI::EMAINMENU::EN_FIND_STUDENT:
				_Engine->getUI()->printData();
				_Engine->getUI()->findStudent();
				break;

			case UI::EMAINMENU::EN_SORT_STUDENT:
				_Engine->getUI()->printData();
				_Engine->getUI()->printSortMenu();
				break;

			case UI::EMAINMENU::EN_MAKE_DUMMY:
				_Engine->getUI()->printData();
				_Engine->makeDummyData(10);
				break;

			case UI::EMAINMENU::EN_EXIT:
				break;

			default:
				_Engine->getUI()->printData();
				_Engine->getUI()->printMainMenu();
				break;
		}

		if (key == UI::EMAINMENU::EN_EXIT)
		{
			break;
		}
		else
		{
			_Engine->getUI()->redraw();
		}
		
	}
}