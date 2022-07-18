#include "UI.h"

void UI::printData()
{
	system("cls");
	std::cout << " ============================================================= " << std::endl;
	std::cout << " ====================== Student Manager ====================== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
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
	std::cout << " ============================================================= " << std::endl;
}

void UI::printStudentData(student& _student)
{
	std::cout << std::setw(5) << std::right << _student.getID();
	std::cout << std::setw(7) << std::right << _student.getName();
	std::cout << std::setw(6) << std::right << _student.getAge();
	std::cout << std::setw(6) << std::right << _student.getScore(ESUBJECT::EN_KOR);
	std::cout << std::setw(6) << std::right << _student.getScore(ESUBJECT::EN_ENG);
	std::cout << std::setw(6) << std::right << _student.getScore(ESUBJECT::EN_MATH);
	std::cout << std::setw(6) << std::right << _student.getScore(ESUBJECT::EN_SOCI);
	std::cout << std::setw(6) << std::right << _student.getScore(ESUBJECT::EN_SCI);
	std::cout << std::setw(7) << std::right << _student.getTotalScore();
	std::cout << std::setw(7) << std::right << _student.getAverageScore() << std::endl;
}

void UI::printMainMenu()
{
	std::cout << " ============================================================= " << std::endl;
	std::cout << " ===== Menu                   Key                        ===== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
	std::cout << " ===== Insert New Student     (0)                        ===== " << std::endl;
	std::cout << " ===== Erase Student          (1)                        ===== " << std::endl;
	std::cout << " ===== Find Student           (2)                        ===== " << std::endl;
	std::cout << " ===== Sort Student           (3)                        ===== " << std::endl;
	std::cout << " ===== Make Dummy             (4)                        ===== " << std::endl;
	std::cout << " ===== Exit                   (ESC)                      ===== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
}

void UI::printSortMenu()
{
	std::cout << " ============================================================= " << std::endl;
	std::cout << "  Sort Student                                           ===== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
	std::cout << " ===== Sort by ID     (Ascending)     (0)                ===== " << std::endl;
	std::cout << " ===== Sort by ID     (Decending)     (1)                ===== " << std::endl;
	std::cout << " ===== Sort by Name   (Ascending)     (2)                ===== " << std::endl;
	std::cout << " ===== Sort by Name   (Decending)     (3)                ===== " << std::endl;
	std::cout << " ===== Sort by Age    (Ascending)     (4)                ===== " << std::endl;
	std::cout << " ===== Sort by Age    (Decending)     (5)                ===== " << std::endl;
	std::cout << " ===== Sort by Score  (Ascending)     (6)                ===== " << std::endl;
	std::cout << " ===== Sort by Score  (Decending)     (7)                ===== " << std::endl;
	std::cout << " ===== Exit                           (9)                ===== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
}

void UI::printInsertStudent()
{
	std::cout << " ============================================================= " << std::endl;
	std::cout << "  Insert New Student                                     ===== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
	std::cout << " Name: ";
	std::string name;
	std::cin >> name;

	std::cout << " Age: ";
	int age;
	std::cin >> age;

	std::cout << " Kor: ";
	int scoreKor;
	std::cin >> scoreKor;

	std::cout << " Eng: ";
	int scoreEng;
	std::cin >> scoreEng;

	std::cout << " Math: ";
	int scoreMath;
	std::cin >> scoreMath;

	std::cout << " Soci: ";
	int scoreSoci;
	std::cin >> scoreSoci;

	std::cout << " Sci: ";
	int scoreSci;
	std::cin >> scoreSci;

	student newStudent(name, age);
	newStudent.setScore(ESUBJECT::EN_KOR, scoreKor);
	newStudent.setScore(ESUBJECT::EN_ENG, scoreEng);
	newStudent.setScore(ESUBJECT::EN_MATH, scoreMath);
	newStudent.setScore(ESUBJECT::EN_SOCI, scoreSoci);
	newStudent.setScore(ESUBJECT::EN_SCI, scoreSci);

	studentManager->insertStudent(newStudent);
}

void UI::eraseStudent()
{
	std::cout << " ============================================================= " << std::endl;
	std::cout << "  Erase Student                                          ===== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
	std::cout << " target ID: ";
	int id;
	std::cin >> id;
	if (!studentManager->eraseStudent(id))
	{
		std::cout << " Can't find id[" << id << "]" << std::endl;
		std::cout << " Please retry again." << std::endl;
	}
	else
	{
		
	}
}

void UI::findStudent()
{
	std::cout << " ============================================================= " << std::endl;
	std::cout << "  Find Student                                           ===== " << std::endl;
	std::cout << " ============================================================= " << std::endl;
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

void UI::redraw()
{
	printData();
	printMainMenu();
}