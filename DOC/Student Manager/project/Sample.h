#pragma once
#include "studentMgr.h"

void StackTestFunc()
{
	LL::Stack<int> StackTest;
	int size = 10;

	std::cout << "Stack Test" << std::endl;

	// push test
	for (int i = 0; i < size; i++)
	{
		int data = (i + 1) * 10;
		StackTest.push(data);
		std::cout << "Stack Push: " << data << std::endl;
	}

	// size, top, pop test
	size_t sizeStack = StackTest.size();
	for (int i = 0; i < sizeStack; i++)
	{
		std::cout << "Stack Pop: " << StackTest.top() << std::endl;
		StackTest.pop();
	}

	// empty test
	if (StackTest.empty())
	{
		std::cout << "Stack Empty. " << std::endl;
	}
	else
	{
		std::cout << "Stack Not Empty. " << std::endl;
	}

}

void QueueTestFunc()
{
	LL::Queue<int> QueueTest;
	int size = 10;

	std::cout << "Queue Test" << std::endl;

	// push test
	for (int i = 0; i < size; i++)
	{
		int data = (i + 1) * 10;
		QueueTest.push(data);
		std::cout << "Queue Push: " << data << std::endl;
	}

	// size, front, back, pop test
	size_t sizeQueue = QueueTest.size();
	for (int i = 0; i < sizeQueue; i++)
	{
		std::cout << "Queue front: " << QueueTest.front() << ", Quene back: " << QueueTest.back() << std::endl;
		QueueTest.pop();
	}

	// empty test
	if (QueueTest.empty())
	{
		std::cout << "Queue Empty. " << std::endl;
	}
	else
	{
		std::cout << "Queue Not Empty. " << std::endl;
	}

}

void studentTest()
{
	student stuA("ABC", 20);

	stuA.setAge(21);
	stuA.setName("BBC");
	stuA.setScore(ESUBJECT::EN_MATH, 60);
	stuA.setScore(ESUBJECT::EN_KOR, 50);
	stuA.setScore(ESUBJECT::EN_ENG, 40);

	std::cout << "Name: " << stuA.getName() << ", age: " << stuA.getAge() << std::endl;
	std::cout << "Math: " << stuA.getScore(ESUBJECT::EN_MATH) << ", Kor: "
		<< stuA.getScore(ESUBJECT::EN_KOR) << ", Eng: " << stuA.getScore(ESUBJECT::EN_ENG) << std::endl;

	stuA.eraseSubject(ESUBJECT::EN_MATH);
	std::cout << "after erase math score." << std::endl;
	std::cout << "Math: " << stuA.getScore(ESUBJECT::EN_MATH) << ", Kor: "
		<< stuA.getScore(ESUBJECT::EN_KOR) << ", Eng: " << stuA.getScore(ESUBJECT::EN_ENG) << std::endl;

}

void studentMgrTest()
{
	studentMgr studentManager;

	student stuA("CCC", 20);
	stuA.setScore(ESUBJECT::EN_MATH, 60);
	stuA.setScore(ESUBJECT::EN_KOR, 50);
	stuA.setScore(ESUBJECT::EN_ENG, 40);

	student stuB("AAA", 24);
	stuA.setScore(ESUBJECT::EN_MATH, 66);
	stuB.setScore(ESUBJECT::EN_KOR, 54);
	stuB.setScore(ESUBJECT::EN_ENG, 39);

	student stuC("BBB", 22);
	stuC.setScore(ESUBJECT::EN_MATH, 32);
	stuC.setScore(ESUBJECT::EN_KOR, 80);
	stuC.setScore(ESUBJECT::EN_ENG, 50);

	studentManager.insertStudent(stuA);
	studentManager.insertStudent(stuB);
	studentManager.insertStudent(stuC);

	student& stuUnknown = studentManager.getStudent(2);

	std::string name = stuUnknown.getName();
	int age = stuUnknown.getAge();
	int score_math = stuUnknown.getScore(ESUBJECT::EN_MATH);
	int score_kor = stuUnknown.getScore(ESUBJECT::EN_KOR);
	int score_eng = stuUnknown.getScore(ESUBJECT::EN_ENG);

	stuUnknown.setScore(ESUBJECT::EN_MATH, 44);

	std::cout << "Name: " << stuUnknown.getName() << ", age: " << stuUnknown.getAge() << std::endl;
	std::cout << "Math: " << stuUnknown.getScore(ESUBJECT::EN_MATH) << ", Kor: "
		<< stuUnknown.getScore(ESUBJECT::EN_KOR) << ", Eng: " << stuUnknown.getScore(ESUBJECT::EN_ENG) << std::endl;

	studentManager.sortScore(ESUBJECT::EN_KOR);
	studentManager.sortID();
	studentManager.sortName();
	studentManager.sortAge();

	int a = 0;
}