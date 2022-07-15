#pragma once

namespace LL
{
	template <typename T>
	struct node
	{
		T		data;
		node*	prev;
		node*	next;

		node() : data(T()), prev(nullptr), next(nullptr) {};
	};

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	// 
	// List
	//
	// STL List Member Function List
	// 
	// -assign: delete all element & insert new elements.
	// -back: return last element.
	// -begin: return iterator of first element.
	// -cbegin: return const iterator of first element.
	// -cend: return const iterator of last element.
	// -clear: delete all element.
	// -crbegin: return reversed const iterator of first element. (= cend)
	// -crend : return reversed const iterator of last element. (= cbegin)
	// -emplace: insert element.
	// -emplace_back: insert element. (pusb_back)
	// -emplace_front: insert element. (push_front)
	// empty: return true or false.
	// -end: return iterator of last element.
	// -erase: delete element or delete element of selected area.
	// -front: return first element.
	// -get_allocator: return copy of allocator.
	// insert: insert element or insert elements of selected area.
	// max_size: return maximum List length.
	// merge: delete element and insert element to List, sort asec, desc, etc.
	// pop_back: delete last element.
	// pop_front: delete first element.
	// push_back: insert element at last.
	// push_front: insert element at first.
	// rbegin: return reversed iterator of first element. (= end)
	// resize: resize.
	// reverse: reverse List.
	// size: return element amount.
	// sort: sort asec, desc, etc.
	// splice: delete element and insert element at other List.
	// swap: swap elements with other List.
	// unique: delete same element.
	// 
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	template <typename T>
	class List //: public LinkedListBase<T>
	{
		private:
			node<T>*	head;
			node<T>*	tail;
			size_t		dataSize = 0;

		public:
			List();
			~List();

			// iterator
			class iterator
			{
				private:
					node<T>* cur;

				public:
					iterator(node<T>* _node = nullptr) : cur(_node) {};

					iterator& operator++()
					{
						cur = cur->next;
						return *this;
					}

					iterator operator++(int)
					{
						iterator temp = *this;
						++* this;
						return temp;
					}

					iterator& operator--()
					{
						cur = cur->prev;
						return *this;
					}

					iterator operator--(int)
					{
						iterator temp = *this;
						--* this;
						return temp;
					}

					node<T>* operator&()
					{
						return cur;
					}

					T& operator*()
					{
						return cur->data;
					}

					bool operator !=(iterator _cmp)
					{
						return (cur != _cmp.cur);
					}

					//bool operator ==(iterator& _cmp)
					bool operator ==(iterator _cmp)
					{
						return (cur == _cmp.cur);
					}
			};

			T& operator[](int _idx)
			{
				iterator iter = begin();
				for (int cnt = 0; cnt < _idx; cnt++)
				{
					++iter;
				}
				return *iter;
			}

			// -assign: delete all element & insert new elements.
			void	assign(int _count, T& _data = 0);
			void	assign(List& _list);
			void	assign(iterator _first, iterator _last);

			// -back: return last element.
			T& back();

			// -begin: return iterator of first element.
			iterator begin() { return iterator(head->next); }

			// -cbegin: return const iterator of first element.
			const iterator cbegin() { return iterator(head->next); }

			// end: return iterator of tail(!= last element).
			//		last element == --end()
			iterator end() { return iterator(tail); }

			// -cend: return const iterator of last element.
			const iterator cend() { return iterator(tail); }

			// -clear: delete all element.
			void clear();

			// -erase: delete element or delete element of selected area.
			void erase(iterator _iter);
			void erase(iterator _first, iterator _last);

			// -front: return first element.
			T& front();

			// insert: insert element or insert elements of selected area.
			void insert(iterator _iter, T& _data);

			// merge: delete element and insert element to List, sort asec, desc, etc.

			// pop_back: delete last element.
			void pop_back();

			// pop_front: delete first element.
			void pop_front();

			// push_back: insert element at last.
			void push_back(T& _data);

			// push_front: insert element at first.
			void push_front(T& _data);

			// swap: swap element.
			void swap(iterator _iter1, iterator _iter2);

			// swap: swap elements with other List.

			// sort: sort asec, desc, etc.
			void sort(iterator _first, iterator _last, bool(*_comparisonFunc)(T&, T&));

			// empty: return true or false.
			bool		empty();

			// size: return element amount.
			size_t		size();

			// -emplace: insert element.
			void		emplace(T& _data);


			// max_size: return maximum List length. (Max allocate count)
			// rbegin: return reversed iterator of first element. (= end)
			// resize: resize.
			// reverse: reverse List.
			// sort: sort asec, desc, etc.
			// splice: delete element and insert element at other List.
			// unique: delete same element.
			// -crbegin: return reversed const iterator of first element. (= cend)
			// -crend : return reversed const iterator of last element. (= cbegin)
			// -get_allocator: return copy of allocator.

			// -emplace_back: insert element. (pusb_back)
			void emplace_back(T& _data);

			// -emplace_front: insert element. (push_front)
			void emplace_front(T& _data);
	};

	template<typename T>
	inline void List<T>::assign(int _count, T& _data)
	{
		for (int cnt = 0; cnt < _count; cnt++)
		{
			push_back(_data);
		}
	}

	template<typename T>
	inline void List<T>::assign(List& _list)
	{
		clear();
		iterator first = _list.begin();
		iterator last = _list.end();
		while (first != last)
		{
			push_back(*first);
			first++;
		}
	}

	template<typename T>
	inline void List<T>::assign(iterator _first, iterator _last)
	{
		clear();
		while (_first != _last)
		{
			push_back(*_first);
			_first++;
		}
	}

	template<typename T>
	inline T& List<T>::back()
	{
		node<T>* curNode = tail->prev;
		return curNode->data;
	}

	template<typename T>
	inline void List<T>::clear()
	{
		while (!empty())
		{
			pop_back();
		}
	}

	template<typename T>
	inline void List<T>::emplace_back(T& _data)
	{
		push_back(_data);
	}

	template<typename T>
	inline void List<T>::emplace_front(T& _data)
	{
		push_front(_data);
	}

	template<typename T>
	inline void List<T>::erase(iterator _iter)
	{
		node<T>* selectedNode = &_iter;
		node<T>* prevNode = selectedNode->prev;
		node<T>* nextNode = selectedNode->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		delete selectedNode;
		dataSize--;
	}

	template<typename T>
	inline void List<T>::erase(iterator _first, iterator _last)
	{
		node<T>* selectedFirst = &_first;
		node<T>* newFirst = selectedFirst->prev;
		node<T>* selectedLast = &_last;
		newFirst->next = selectedLast;
		selectedLast->prev = newFirst;

		for (iterator iter = _first; iter != _last; )
		{
			node<T>* deleteNode = &iter;
			iter++;
			delete deleteNode;
			dataSize--;
		}
	}

	template<typename T>
	inline T& List<T>::front()
	{
		node<T>* curNode = head->next;
		return curNode->data;
	}

	template<typename T>
	inline void List<T>::insert(iterator _iter, T& _data)
	{
		node<T>* nowPos = &_iter;
		node<T>* prevNode = nowPos->prev;
		node<T>* newNode = new node<T>;
		newNode->data = _data;

		prevNode->next = newNode;
		newNode->prev = prevNode;
		newNode->next = nowPos;
		nowPos->prev = newNode;
		dataSize++;
	}

	template<typename T>
	inline List<T>::List()
	{
		head = new node<T>;
		tail = new node<T>;
		head->next = tail;
		tail->prev = head;
		dataSize = 0;
	}

	template<typename T>
	inline List<T>::~List()
	{
		clear();
		delete head;
		delete tail;
	}

	template<typename T>
	inline void List<T>::pop_back()
	{
		erase(--end());
	}

	template<typename T>
	inline void List<T>::pop_front()
	{
		erase(begin());
	}

	template<typename T>
	inline void List<T>::push_back(T& _data)
	{
		insert(end(), _data);
	}

	template<typename T>
	inline void List<T>::push_front(T& _data)
	{
		insert(begin(), _data);
	}

	template<typename T>
	inline void List<T>::swap(iterator _iter1, iterator _iter2)
	{
		node<T>* node1 = &_iter1;
		node<T>* node2 = &_iter2;

		node<T>* prev_1 = node1->prev;
		node<T>* next_1 = node1->next;
		node<T>* prev_2 = node2->prev;
		node<T>* next_2 = node2->next;

		if ((next_1 != node2) && (prev_1 != node2))
		{
			// node2 move
			node2->prev = node1->prev;
			node2->next = node1->next;
			prev_1->next = node2;
			next_1->prev = node2;

			// node1 move
			node1->prev = prev_2;
			node1->next = next_2;
			prev_2->next = node1;
			next_2->prev = node1;
		}
		else
		{
			// node2 move
			node2->prev = node1->prev;
			prev_1->next = node2;
			node1->prev = node2;
			node2->next = node1;

			// node1 move
			next_2->prev = node1;
			node1->next = next_2;
		}

	}

	template<typename T>
	inline void List<T>::sort(iterator _first, iterator _last, bool(*_comparisonFunc)(T&, T&))
	{
		bool bTest = false;
		// Qsort Test
		//if (false)
		//{
		//	iterator pivot = _first;
		//	T& pivotVal = *pivot;

		//	iterator left = _first;
		//	left++;

		//	iterator borderLeft = left;
		//	borderLeft++;
		//	iterator right = _last;
		//	if (_last == end())
		//	{
		//		right--;
		//	}

		//	if (_comparisonFunc == nullptr)
		//	{
		//		_comparisonFunc = [](T& _a, T& _b)
		//		{
		//			return _a < _b;
		//		};
		//	}

		//	int leftMoveCnt = 0;
		//	int rightMoveCnt = 0;
		//	if (_dataSize == NULL)
		//	{
		//		_dataSize = dataSize;
		//	}

		//	while (((leftMoveCnt + rightMoveCnt) < (_dataSize - 1)) && (right != borderLeft))
		//	{
		//		//while ((left != _last) && (pivotVal < *left))
		//		while ((left != _last) && _comparisonFunc(*left, pivotVal))
		//		{
		//			left++;
		//			leftMoveCnt++;
		//		}

		//		//while ((right != pivot) && (*right < pivotVal))
		//		while ((right != borderLeft) && _comparisonFunc(pivotVal, *right))
		//		{
		//			right--;
		//			rightMoveCnt++;
		//		}

		//		if ((leftMoveCnt + rightMoveCnt) < (_dataSize - 1))
		//		{
		//			swap(left, right);
		//		}
		//	}

		//	if ((leftMoveCnt + rightMoveCnt) >= (_dataSize - 1))
		//	{
		//		swap(pivot, right);
		//	}
		//	iterator last = pivot;
		//	iterator first = pivot;
		//	sort(right, --last, _comparisonFunc, (_dataSize - rightMoveCnt - 1));
		//	sort(++first, _last, _comparisonFunc, (_dataSize - leftMoveCnt - 1));
		//}
		
		// Buble sort
		
		if (!bTest)
		{
			iterator IterlastElement = _last;
			IterlastElement--;

			for (iterator iter = _first; iter != _last; iter++)
			{
				for (iterator iter2 = _first; iter2 != IterlastElement; iter2++)
				{
					iterator next = iter2;
					next++;
					if (!_comparisonFunc(*iter2, *next))
					{
						T temp = *iter2;
						*iter2 = *next;
						*next = temp;
					}
				}
			}
		}
	}

	template<typename T>
	inline bool List<T>::empty()
	{
		if (dataSize > 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	template<typename T>
	inline size_t List<T>::size()
	{
		return dataSize;
	}

	template<typename T>
	inline void List<T>::emplace(T& _data)
	{
		push_back(_data);
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	// 
	// Stack (Last-In, First-Out)
	//
	// STL Stack Member Function List
	//
	// empty: return true or false.
	// size: return element amount.
	// -top: return last element. (pop_back) - Stack Original Function
	// push: insert element. (push_back)
	// emplace: construct and insert element.
	// pop: remove last element.
	// swap: swap contents.
	//
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	template <typename T>
	class Stack
	{
		private:
			LL::List<T>* stackList;

		public:
			Stack() { stackList = new List<T>; };
			~Stack() { delete stackList; };

			T& top() { return stackList->back(); };
			void	push(T& _data) { stackList->push_back(_data); };
			void	pop() { stackList->pop_back(); };
			size_t	size() { return stackList->size(); };
			bool	empty() { return stackList->empty(); };
	};
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	// 
	// Queue (First-In, First-Out)
	// 
	// STL Queue Member Function List
	//
	// empty: return true or false.
	// size: return element amount.
	// -front: return first element. (pop_front) - Queue Original Function
	// -back: return last element. (pop_back) - Queue Original Function
	// push: insert element. (push_back)
	// emplace: construct and insert element.
	// pop: remove first element.
	// swap: swap contents.
	//
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	template <typename T>
	class Queue
	{
		private:
			LL::List<T>* queueList;

		public:
			Queue() { queueList = new List<T>; };
			~Queue() { delete queueList; };

			T& front() { return *queueList->begin(); };
			T& back() { return queueList->back(); };
			void	push(T& _data) { queueList->push_back(_data); };
			void	pop() { queueList->pop_front(); };
			size_t	size() { return queueList->size(); };
			bool	empty() { return queueList->empty(); };
	};
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
}