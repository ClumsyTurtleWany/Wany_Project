#include <iostream>
#include "main.h"
#include "LinkedList.hpp"
#include <string>
#include "StudentMgr.h"
#include <list>

bool asce(int& _a, int& _b)
{
	return _a < _b;
}

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

void ListTestFunc()
{
	//// Linked List List
	//LL::List<int> LL_List;

	//// push_back Test
	//for (int i = 0; i < 10; i++)
	//{
	//	int data = (i + 1) * 10;
	//	LL_List.push_back(data);
	//}

	//// iterator test
	//for (auto iter = LL_List.begin(); iter != LL_List.end(); ++iter)
	//{
	//	std::cout << *iter << std::endl;
	//}

	//LL::List<int>::iterator iter1 = LL_List.begin();
	//iter1++;
	//iter1++;
	//iter1++;
	//iter1++;
	//iter1++;

	//// swap test
	//LL_List.swap(LL_List.begin(), iter1);
	//int data = 66;

	//// push_front test
	//LL_List.push_front(data);
	//data = 77;
	//LL_List.push_back(data);

	//// sort test
	//LL_List.sort(LL_List.begin(), LL_List.end(), asce);

	//// class push, class sort test
	//LL::List<wany::student> LL_List_stu;
	//wany::student stuA("A", 20, "010-0000-1111");
	//wany::student stuB("B", 22, "010-0000-1111");
	//wany::student stuC("C", 25, "010-0000-1111");
	//wany::student stuD("D", 19, "010-0000-1111");
	//wany::student stuE("E", 21, "010-0000-1111");
	//wany::student stuF("F", 23, "010-0000-1111");
	//wany::student stuG("G", 20, "010-0000-1111");

	//LL_List_stu.push_back(stuA);
	//LL_List_stu.push_back(stuB);
	//LL_List_stu.push_back(stuC);
	//LL_List_stu.push_back(stuD);
	//LL_List_stu.push_back(stuE);
	//LL_List_stu.push_back(stuF);
	//LL_List_stu.push_back(stuG);

	////LL_List_stu.sort(LL_List_stu.begin(), LL_List_stu.end(), asceStu);
}

void studentTest()
{
	student stuA("ABC", 20, "010-0000-1111");

	stuA.setAge(21);
	stuA.setName("BBC");
	stuA.setPhone("010-1111-0000");
	stuA.setScore(ESUBJECT::EN_MATH, 60);
	stuA.setScore(ESUBJECT::EN_KOR, 50);
	stuA.setScore(ESUBJECT::EN_ENG, 40);

	std::cout << "Name: " << stuA.getName() << ", age: " << stuA.getAge() << ", phone: " << stuA.getPhone() << std::endl;
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

	student stuA("ABC", 20, "010-0000-1111");
	stuA.setScore(ESUBJECT::EN_MATH, 60);
	stuA.setScore(ESUBJECT::EN_KOR, 50);
	stuA.setScore(ESUBJECT::EN_ENG, 40);

	student stuB("BBB", 24, "010-0000-1111");
	stuA.setScore(ESUBJECT::EN_MATH, 66);
	stuB.setScore(ESUBJECT::EN_KOR, 54);
	stuB.setScore(ESUBJECT::EN_ENG, 39);

	student stuC("CCC", 22, "010-0000-1111");
	stuC.setScore(ESUBJECT::EN_MATH, 32);
	stuC.setScore(ESUBJECT::EN_KOR, 80);
	stuC.setScore(ESUBJECT::EN_ENG, 50);

	studentManager.insertStudent(stuA);
	studentManager.insertStudent(stuB);
	studentManager.insertStudent(stuC);

	student& stuUnknown = studentManager.getStudent(2);

	std::string name = stuUnknown.getName();
	int age = stuUnknown.getAge();
	std::string phone = stuUnknown.getPhone();
	int score_math = stuUnknown.getScore(ESUBJECT::EN_MATH);
	int score_kor = stuUnknown.getScore(ESUBJECT::EN_KOR);
	int score_eng = stuUnknown.getScore(ESUBJECT::EN_ENG);

	stuUnknown.setScore(ESUBJECT::EN_MATH, 44);

	std::cout << "Name: " << stuUnknown.getName() << ", age: " << stuUnknown.getAge() << ", phone: " << stuUnknown.getPhone() << std::endl;
	std::cout << "Math: " << stuUnknown.getScore(ESUBJECT::EN_MATH) << ", Kor: "
		<< stuUnknown.getScore(ESUBJECT::EN_KOR) << ", Eng: " << stuUnknown.getScore(ESUBJECT::EN_ENG) << std::endl;

	studentManager.sortScore(ESUBJECT::EN_KOR);

	int a = 0;
}

int main()
{
	//StackTestFunc();
	//QueueTestFunc();
	//ListTestFunc();
	//studentTest();
	studentMgrTest();

	return 0;
}
