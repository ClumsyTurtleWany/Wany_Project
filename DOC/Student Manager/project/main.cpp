#include "main.h"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	studentMgr* studentManager = new studentMgr;
	UI* mainUI = new UI(studentManager);

	mainUI->runDisplay();
	
	WaitForSingleObject(mainUI->getExitThread(), INFINITE);

	delete mainUI;
	delete studentManager;
	
	return 0;
}