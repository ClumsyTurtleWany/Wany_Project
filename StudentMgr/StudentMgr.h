#pragma once
#include <string>
#include "LinkedList.hpp"


enum class ESUBJECT
{
	EN_KOR,
	EN_ENG,
	EN_MATH,
	EN_SOCI,
	EN_SCI,
	UNKNOWN
};

struct subject
{
	ESUBJECT sub;
	int score;

	subject() : sub(ESUBJECT::UNKNOWN), score(0) {};
	subject(ESUBJECT _subject, int _score) : sub(_subject), score(_score) {};
};

class student
{
private:
	int id;
	std::string name;
	int age;
	std::string phone;
	LL::List<subject>* subjects;	

public:
	student(std::string _name = "", int _age = 0, std::string _phone = "") : name(_name), age(_age), phone(_phone) 
	{
		subjects = new LL::List<subject>;
	};
	~student() { delete subjects; };

	void setName(std::string _str) { name = _str; };
	void setAge(int _age) { age = _age; };
	void setPhone(std::string _num) { phone = _num; };
	void setScore(subject& _subject) { subjects->push_back(_subject); };
	void setScore(ESUBJECT _subject, int _score);
	void setID(int _id) { id = _id; };

	int getID() { return id; };
	int getAge() { return age; };
	std::string getName() { return name; };
	std::string getPhone() { return phone; };
	int getScore(ESUBJECT _subject);
	bool eraseSubject(ESUBJECT _subject);
	LL::List<subject>::iterator findSubject(ESUBJECT _subject);	
};

class studentMgr
{
private:
	LL::List<student>* studentList;
	int cnt_id = 0;

public:
	studentMgr()
	{
		studentList = new LL::List<student>;
	}
	~studentMgr()
	{
		delete studentList;
	}

	void insertStudent(student& _student);
	bool eraseStudent(int _id);
	student& getStudent(int _id);
	LL::List<student>::iterator findID(int _id);
	LL::List<student>::iterator findName(std::string _name);
	
};

