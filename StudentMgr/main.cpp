#include <iostream>
#include "main.h"
#include "LinkedList.hpp"
#include <list>
#include <string>
#include <algorithm>

class student
{
private:
	std::string name;
	int age;
	std::string phone;

public:
	student(std::string _name = "", int _age = 0, std::string _phone = "") : name(_name), age(_age), phone(_phone) {};
	~student() {};

	void setName(std::string _str) { name = _str; };
	void setAge(int _age) { age = _age; };
	void setPhone(std::string _num) { phone = _num; };

	std::string getName() { return name; };
	int getAge() { return age; };
	std::string getPhone() { return phone; };
};

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

bool asce(int& _a, int& _b)
{
	return _a < _b;
}

int main()
{
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

	LL::List<int>::iterator iter1 = LL_List.begin();
	iter1++;
	iter1++;
	iter1++;
	iter1++;
	iter1++;

	LL_List.swap(LL_List.begin(), iter1);
	int data = 66;
	LL_List.push_front(data);
	data = 77;
	LL_List.push_back(data);

	//LL_List_cl.swap(LL_List_cl.begin(), --LL_List_cl.end());

	LL_List.sort(LL_List.begin(), --LL_List.end(), asce);

	int a = 0;
	return 0;
}
