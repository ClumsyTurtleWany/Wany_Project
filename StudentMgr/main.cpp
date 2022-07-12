#include <iostream>
#include "main.h"
#include "LinkedList.hpp"
#include <list>
#include <string>

class student
{
private:
	std::string name;
	int age;
	std::string phone;

public:
	student(std::string _name = "", int _age = 0, std::string _phone = "") : name(_name), age(_age), phone(_phone) {};

	void setName(std::string _str) { name = _str; };
	void setAge(int _age) { age = _age; };
	void setPhone(std::string _num) { phone = _num; };

	std::string getName() { return name; };
	int getAge() { return age; };
	std::string getPhone() { return phone; };
};

void githubTest()
{
	// push?
}

template <typename T>
struct node
{
	const T		data;
	node* prev;
	node* next;
	node() = default;
	node(const node&) = delete;
	node& operator=(const node&) = delete;
};

void main()
{
	// Std List
	std::list<int> stdList;
	for (int i = 0; i < 10; i++)
	{
		stdList.push_back((i + 1) * 10);
	}

	for (auto iter = stdList.begin(); iter != stdList.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}

	// Linked List List
	LL::List<int> LL_List;
	for (int i = 0; i < 10; i++)
	{
		int data = (i + 1) * 10;
		LL_List.push_back(data);
	}

	for (auto iter = LL_List.begin(); iter != LL_List.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}

	std::list<student> stdList_cl;

	student stu_A("AAA", 20, "010-0000-0000");
	student stu_B("BBB", 27, "010-1111-0000");
	student stu_C("CCC", 31, "010-0000-1111");

	stdList_cl.push_back(stu_A);
	stdList_cl.push_back(stu_B);
	stdList_cl.push_back(stu_C);

	LL::List<student> LL_List_cl;

	LL_List_cl.push_back(stu_A);
	LL_List_cl.push_back(stu_B);
	LL_List_cl.push_back(stu_C);

	student stu_test = LL_List_cl[0];
	std::string strName = LL_List_cl[0].getName();
	
}
