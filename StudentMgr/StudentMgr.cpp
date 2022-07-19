#include "StudentMgr.h"

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// student Class
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

LL::List<subject>::iterator student::findSubject(ESUBJECT _subject)
{
	bool bFind = false;
	size_t listSize = subjects.size();
	for (auto it = subjects.begin(); it != subjects.end(); it++)
	{
		subject temp = *it;
		if (temp.sub == _subject)
		{
			bFind = true;
			return it;
		}
	}

	if (!bFind)
	{
		return nullptr;
	}
}

void student::setScore(ESUBJECT _subject, int _score)
{
	auto it = findSubject(_subject);
	if (it != nullptr)
	{
		subject temp = *it;
		temp.score = _score;
		*it = temp;
	}
	else
	{
		subject* temp = new subject(_subject, _score);
		subjects.push_back(*temp);
	}
}

int student::getScore(ESUBJECT _subject)
{
	auto it = findSubject(_subject);
	if (it != nullptr)
	{
		subject temp = *it;
		return temp.score;
	}
	else
	{
		return NULL;
	}
}

int student::getTotalScore()
{
	int total = 0;
	total += getScore(ESUBJECT::EN_KOR);
	total += getScore(ESUBJECT::EN_ENG);
	total += getScore(ESUBJECT::EN_MATH);
	total += getScore(ESUBJECT::EN_SOCI);
	total += getScore(ESUBJECT::EN_SCI);
	return total;
}

double student::getAverageScore()
{
	double total = static_cast<double>(getTotalScore());
	size_t size = subjects.size();
	return (total / size);
}

bool student::eraseSubject(ESUBJECT _subject)
{
	auto it = findSubject(_subject);
	if (it != nullptr)
	{
		subjects.erase(it);
		return true;
	}
	else
	{
		return false;
	}
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// studentMgr Class
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void studentMgr::insertStudent(student& _student)
{
	//student* newStudent = new student;
	if (_student.getID() == NULL)
	{
		_student.setID(++cnt_id);
	}
	studentList.push_back(_student);
}

bool studentMgr::eraseStudent(int _id)
{
	auto it = findID(_id);
	if (it != nullptr)
	{
		studentList.erase(it);
		return true;
	}
	else
	{
		return false;
	}
}

LL::List<student>::iterator studentMgr::findID(int _id)
{
	bool bFind = false;
	size_t listSize = studentList.size();
	for (auto it = studentList.begin(); it != studentList.end(); it++)
	{
		if ((*it).getID() == _id)
		{
			bFind = true;
			return it;
		}
	}

	if (!bFind)
	{
		return nullptr;
	}
}

LL::List<student>::iterator studentMgr::findName(std::string _name)
{
	bool bFind = false;
	size_t listSize = studentList.size();
	for (auto it = studentList.begin(); it != studentList.end(); it++)
	{
		if ((*it).getName() == _name)
		{
			bFind = true;
			return it;
		}
	}

	if (!bFind)
	{
		return nullptr;
	}
}

 bool studentMgr::findNameAll(std::string _name, LL::List<student>& _list)
{
	bool bFind = false;
	size_t listSize = studentList.size();
	std::string nameUpper;
	for (int i = 0; i < _name.size(); i++)
	{
		nameUpper.push_back(toupper(_name[i]));
	}

	for (auto it = studentList.begin(); it != studentList.end(); it++)
	{
		std::string name = (*it).getName();
		for (int i = 0; i < name.size(); i++)
		{
			name[i] = toupper(name[i]);
		}
		if (name == nameUpper)
		{
			bFind = true;
			_list.push_back(*it);
		}
	}

	if (!bFind)
	{
		return false;
	}
	else
	{
		return true;
	}
}

student& studentMgr::getStudent(int _id)
{
	bool bFind = false;
	auto it = findID(_id);
	if (it != nullptr)
	{
		bFind = true;
		return *it;
	}
}

LL::List<student>::iterator studentMgr::begin()
{
	return studentList.begin();
}

LL::List<student>::iterator studentMgr::end()
{
	return studentList.end();
}

const size_t studentMgr::getSize()
{
	return studentList.size();
}

void studentMgr::sortScore(ESUBJECT _subject, bool _ascending)
{
	if (!_ascending)
	{
		studentList.sort(studentList.begin(), studentList.end(),
			[_subject](student& _a, student& _b)
			{
				return _a.getScore(_subject) > _b.getScore(_subject);
			});
	}
	else
	{
		studentList.sort(studentList.begin(), studentList.end(),
			[_subject](student& _a, student& _b)
			{
				return _a.getScore(_subject) < _b.getScore(_subject);
			});
	}
}

void studentMgr::sortID(bool _ascending)
{
	if (!_ascending)
	{
		studentList.sort(studentList.begin(), studentList.end(),
			[](student& _a, student& _b)
			{
				return _a.getID() > _b.getID();
			});
	}
	else
	{
		studentList.sort(studentList.begin(), studentList.end(),
			[](student& _a, student& _b)
			{
				return _a.getID() < _b.getID();
			});
	}
}

void studentMgr::sortName(bool _ascending)
{
	if (!_ascending)
	{
		studentList.sort(studentList.begin(), studentList.end(),
			[](student& _a, student& _b)
			{
				return _a.getName() > _b.getName();
			});
	}
	else
	{
		studentList.sort(studentList.begin(), studentList.end(),
			[](student& _a, student& _b)
			{
				return _a.getName() < _b.getName();
			});
	}
}

void studentMgr::sortAge(bool _ascending)
{
	if (!_ascending)
	{
		studentList.sort(studentList.begin(), studentList.end(),
			[](student& _a, student& _b)
			{
				return _a.getAge() > _b.getAge();
			});
	}
	else
	{
		studentList.sort(studentList.begin(), studentList.end(),
			[](student& _a, student& _b)
			{
				return _a.getAge() < _b.getAge();
			});
	}
}

bool studentMgr::saveFile(std::string _name)
{
	std::fstream file(_name, std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
	if (!file.is_open())
	{
		std::cout << _name << " open failed." << std::endl;
		return false;
	}
	else
	{
		if (!studentList.empty())
		{
			file << cnt_id << std::endl;
			file << "id,name,age,kor,eng,math,soci,sci,total,aver" << std::endl;
			for (auto it = studentList.begin(); it != studentList.end(); it++)
			{
				/*if (it != studentManager->begin())
				{
					std::cout << std::endl;
				}*/
				file << (*it).getID() << ","
					<< (*it).getName() << ","
					<< (*it).getAge() << ","
					<< (*it).getScore(ESUBJECT::EN_KOR) << ","
					<< (*it).getScore(ESUBJECT::EN_ENG) << ","
					<< (*it).getScore(ESUBJECT::EN_MATH) << ","
					<< (*it).getScore(ESUBJECT::EN_SOCI) << ","
					<< (*it).getScore(ESUBJECT::EN_SCI) << ","
					<< (*it).getTotalScore() << ","
					<< (*it).getAverageScore() << std::endl;
			}

			file.close();
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool studentMgr::loadFile(std::string _name)
{
	std::fstream file(_name);
	if (!file.is_open())
	{
		return false;
	}
	else
	{
		if (!file.eof())
		{
			std::string strCntID;
			std::getline(file, strCntID);
			studentList.clear();
			cnt_id = std::stoi(strCntID);

			std::string dummy;
			std::getline(file, dummy);
		}

		int cnt = 0;
		while (!file.eof())
		{
			student loadStudent;
			std::string lineData;
			// ID
			std::getline(file, lineData, ',');
			if (!lineData.empty())
			{
				loadStudent.setID(std::stoi(lineData));
				std::cout << "id: " << lineData << std::endl;

				// Name
				std::getline(file, lineData, ',');
				loadStudent.setName(lineData);
				std::cout << "name: " << lineData << std::endl;

				// Age
				std::getline(file, lineData, ',');
				loadStudent.setAge(std::stoi(lineData));
				std::cout << "age: " << lineData << std::endl;

				// Kor
				std::getline(file, lineData, ',');
				loadStudent.setScore(ESUBJECT::EN_KOR, std::stoi(lineData));
				std::cout << "kor: " << lineData << std::endl;

				// Eng
				std::getline(file, lineData, ',');
				loadStudent.setScore(ESUBJECT::EN_ENG, std::stoi(lineData));
				std::cout << "eng: " << lineData << std::endl;

				// Math
				std::getline(file, lineData, ',');
				loadStudent.setScore(ESUBJECT::EN_MATH, std::stoi(lineData));
				std::cout << "math: " << lineData << std::endl;

				// Soci
				std::getline(file, lineData, ',');
				loadStudent.setScore(ESUBJECT::EN_SOCI, std::stoi(lineData));
				std::cout << "soci: " << lineData << std::endl;

				// Sci
				std::getline(file, lineData, ',');
				loadStudent.setScore(ESUBJECT::EN_SCI, std::stoi(lineData));
				std::cout << "sci: " << lineData << std::endl;

				std::getline(file, lineData, ','); // total
				std::getline(file, lineData, '\n'); // average

				studentList.push_back(loadStudent);
				cnt++;
			}
		}
		file.close();
		return true;
	}
}