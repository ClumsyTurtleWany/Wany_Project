#pragma once
#include <string>
#include <fstream>
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
	LL::List<subject> subjects;	

public:
	student(std::string _name = "", int _age = 0, int _id = NULL) : name(_name), age(_age), id(NULL) {};
	~student() {};

	void setName(std::string _str) { name = _str; };
	void setAge(int _age) { age = _age; };
	void setScore(subject& _subject) { subjects.push_back(_subject); };
	void setScore(ESUBJECT _subject, int _score);
	void setID(int _id) { id = _id; };

	int getID() { return id; };
	int getAge() { return age; };
	std::string getName() { return name; };
	int getScore(ESUBJECT _subject);
	int getTotalScore();
	double getAverageScore();
	bool eraseSubject(ESUBJECT _subject);
	// return iterator of finded subject.
	LL::List<subject>::iterator findSubject(ESUBJECT _subject);	
};

class studentMgr
{
private:
	LL::List<student> studentList;
	int cnt_id = 0;

public:
	studentMgr() {};
	~studentMgr() {};

	void insertStudent(student& _student);
	bool eraseStudent(int _id);
	LL::List<student>::iterator findID(int _id);
	LL::List<student>::iterator findName(std::string _name);
	bool findNameAll(std::string _name, LL::List<student>& _list);
	student& getStudent(int _id);

	LL::List<student>::iterator begin();
	LL::List<student>::iterator end();

	const size_t getSize();

	// sort by subject score.
	// default: decending. (true: ascending, false: decending)
	void sortScore(ESUBJECT _subject, bool _ascending = false);

	// sort by ID.
	// default: ascending. (true: ascending, false: decending)
	void sortID(bool _ascending = true);

	// sort by name.
	// default: ascending. (true: ascending, false: decending)
	void sortName(bool _ascending = true);

	// sort by age.
	// default: ascending. (true: ascending, false: decending)
	void sortAge(bool _ascending = true);

	// File Management
	bool saveFile(std::string _name);
	bool loadFile(std::string _name);
	// need findFile 
};