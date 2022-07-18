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
	_student.setID(++cnt_id);
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


