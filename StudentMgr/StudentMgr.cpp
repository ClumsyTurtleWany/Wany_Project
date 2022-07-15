#include "StudentMgr.h"

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// student Class
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

LL::List<subject>::iterator student::findSubject(ESUBJECT _subject)
{
	bool bFind = false;
	size_t listSize = subjects->size();
	for (auto it = subjects->begin(); it != subjects->end(); it++)
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
		subjects->push_back(*temp);
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

bool student::eraseSubject(ESUBJECT _subject)
{
	auto it = findSubject(_subject);
	if (it != nullptr)
	{
		subjects->erase(it);
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
	_student.setID(++cnt_id);
	studentList->push_back(_student);
}

bool studentMgr::eraseStudent(int _id)
{
	auto it = findID(_id);
	if (it != nullptr)
	{
		studentList->erase(it);
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
	size_t listSize = studentList->size();
	for (auto it = studentList->begin(); it != studentList->end(); it++)
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
	size_t listSize = studentList->size();
	for (auto it = studentList->begin(); it != studentList->end(); it++)
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
	else
	{
		student temp;
		return temp;
	}
}
