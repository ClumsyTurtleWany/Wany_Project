#pragma once

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// History - Wany(KIM DONG WAN)
//
// 2022.07.08 added Linked List Base Class.
// 2022.07.10 added Stack and Queue.
// 2022.07.11 added List.
// 
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
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
// max_size: return maximum list length.
// merge: delete element and insert element to list, sort asec, desc, etc.
// pop_back: delete last element.
// pop_front: delete first element.
// push_back: insert element at last.
// push_front: insert element at first.
// rbegin: return reversed iterator of first element. (= end)
// resize: resize.
// reverse: reverse list.
// size: return element amount.
// sort: sort asec, desc, etc.
// splice: delete element and insert element at other list.
// swap: swap elements with other list.
// unique: delete same element.
// 
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

namespace LL
{
	template <typename T>
	struct node
	{
		T		data;
		node* prev;
		node* next;
	};

	template <typename T>
	class LinkedListBase
	{
		private:
		public:
			/*template <typename T>
			struct node
			{
				T		data;
				node*	prev;
				node*	next;
			} node;*/

		protected:
			node<T>*	head;
			node<T>*	tail;
			size_t		dataSize = 0;

		public:
			LinkedListBase();
			~LinkedListBase();

			// Common Function
			bool		empty();
			size_t		size();
			void		emplace(T& _data);
			//void swap();

		protected:
			// Common Function
			void		release();

			// List Function
			void		push_front(T& _data);
			void		push_back(T& _data);
			void		pop_back();
			void		pop_front();
	};

	template<typename T>
	inline LinkedListBase<T>::LinkedListBase()
	{
		head = nullptr;
		tail = nullptr;
		dataSize = 0;
	}

	template<typename T>
	inline LinkedListBase<T>::~LinkedListBase()
	{
		release();
	}

	template<typename T>
	inline void LinkedListBase<T>::push_front(T& _data)
	{
		node<T>* newNode = new node<T>;
		newNode->data = _data;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = head->prev;
			tail->next = head;
		}

		dataSize++;
	}

	template<typename T>
	inline void LinkedListBase<T>::push_back(T& _data)
	{
		node<T>* newNode = new node<T>;
		newNode->data = _data;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			newNode->prev = tail;
			tail->next = newNode;
			tail = tail->next;
			head->prev = tail;
		}

		dataSize++;
	}

	template<typename T>
	inline void LinkedListBase<T>::pop_back()
	{
		//T _data = tail->data;
		node<T>* curNode = tail->prev;
		delete[] tail;
		tail = curNode;
		dataSize--;
		if (dataSize == 0)
		{
			head = nullptr;
			tail = nullptr;
		}
		//return _data;
	}

	template<typename T>
	inline void LinkedListBase<T>::pop_front()
	{
		//T _data = head->data;
		node<T>* tempNode = head->next;
		delete[] head;
		head = tempNode;
		dataSize--;
		if (dataSize == 0)
		{
			head = nullptr;
			tail = nullptr;
		}
		//return _data;
	}

	template<typename T>
	inline bool LinkedListBase<T>::empty()
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
	inline size_t LinkedListBase<T>::size()
	{
		return dataSize;
	}

	template<typename T>
	inline void LinkedListBase<T>::emplace(T& _data)
	{
		push_back(_data);
	}

	template<typename T>
	inline void LinkedListBase<T>::release()
	{
		while (!empty())
		{
			pop_back();
		}
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
	template <typename T>
	class Stack : public LinkedListBase<T>
	{
	private:
	public:
		Stack() {};
		~Stack() {};
		T& top() { return LinkedListBase<T>::tail->data; };
		void	push(T& _data) { LinkedListBase<T>::push_back(_data); };
		void	pop() { LinkedListBase<T>::pop_back(); };
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
	template <typename T>
	class Queue : public LinkedListBase<T>
	{
	private:
	public:
		Queue() {};
		~Queue() {};
		T& front() { return LinkedListBase<T>::head->data; };
		T& back() { return LinkedListBase<T>::tail->data; };
		void	push(T& _data) { LinkedListBase<T>::push_back(_data); };
		void	pop() { LinkedListBase<T>::pop_front(); };
	};
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
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
	// max_size: return maximum list length.
	// merge: delete element and insert element to list, sort asec, desc, etc.
	// pop_back: delete last element.
	// pop_front: delete first element.
	// push_back: insert element at last.
	// push_front: insert element at first.
	// rbegin: return reversed iterator of first element. (= end)
	// resize: resize.
	// reverse: reverse list.
	// size: return element amount.
	// sort: sort asec, desc, etc.
	// splice: delete element and insert element at other list.
	// swap: swap elements with other list.
	// unique: delete same element.
	// 
	template <typename T>
	class List : public LinkedListBase<T>
	{
	private:
	public:
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

				bool operator !=(iterator& _cmp)
				{
					return (cur != _cmp.cur);
				}

				bool operator ==(iterator& _cmp)
				{
					return (cur == _cmp.cur);
				}
		};

		// -assign: delete all element & insert new elements.
		void	assign(int _count, T& _data = 0);
		//void	assign(List& _list);
		void	assign(iterator _first, iterator _last);

		// -back: return last element.
		T& back();

		// -begin: return iterator of first element.
		iterator begin() {	return iterator(LinkedListBase<T>::head); }

		// -cbegin: return const iterator of first element.
		const iterator cbegin() { return iterator(LinkedListBase<T>::head); }
		
		// -cend: return const iterator of last element.
		// -clear: delete all element.
		void clear();

		// -crbegin: return reversed const iterator of first element. (= cend)
		
		// -crend : return reversed const iterator of last element. (= cbegin)
		
		// -emplace: insert element.
		// -emplace_back: insert element. (pusb_back)
		void emplace_back(T& _data);

		// -emplace_front: insert element. (push_front)
		void emplace_front(T& _data);

		// empty: return true or false.
		
		// -end: return iterator of last element.
		iterator end() { return iterator(LinkedListBase<T>::tail); }

		// -erase: delete element or delete element of selected area.
		void erase(iterator _iter) {};
		void erase(iterator _first, iterator _last) {};

		// -front: return first element.
		T& front() { return LinkedListBase<T>::head->data; }
		
		// -get_allocator: return copy of allocator.
		

		// insert: insert element or insert elements of selected area.
		void insert(iterator _iter, T& _data);

		// max_size: return maximum list length.
		

		// merge: delete element and insert element to list, sort asec, desc, etc.
		

		// pop_back: delete last element.
		void pop_back();

		// pop_front: delete first element.
		void pop_front();

		// push_back: insert element at last.
		void push_back(T& _data);

		// push_front: insert element at first.
		void push_front(T& _data);
		 
		
		// rbegin: return reversed iterator of first element. (= end)
				
		// resize: resize.
		
		// reverse: reverse list.
		
		// size: return element amount.
		
		// sort: sort asec, desc, etc.
		
		// splice: delete element and insert element at other list.
		
		// swap: swap elements with other list.
		
		// unique: delete same element.
	};

	template<typename T>
	inline void List<T>::assign(int _count, T& _data)
	{
		for (int cnt = 0; cnt < _count; cnt++)
		{
			LinkedListBase<T>::push_back(_data);
		}
	}

	/*template<typename T>
	inline void List<T>::assign(List& _list)
	{
		
	}*/

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
		return LinkedListBase<T>::tail->data;
	}

	template<typename T>
	inline void List<T>::clear()
	{
		LinkedListBase<T>::release();
	}

	template<typename T>
	inline void List<T>::emplace_back(T& _data)
	{
		LinkedListBase<T>::push_back(_data);
	}

	template<typename T>
	inline void List<T>::emplace_front(T& _data)
	{
		LinkedListBase<T>::push_front(_data);
	}

	template<typename T>
	inline void List<T>::insert(iterator _iter, T& _data)
	{
		node<T>* nowPos = &_iter;
		node<T>* prevNode = nowPos->prev;
		node<T>* newNode = new node<T>;
		newNode->data = _data;

		/*newNode->prev = prevNode;
		prevNode->next = newNode;
		newNode->next = nowPos;
		nowPos->prev = newNode;*/
		prevNode->next = newNode;
		newNode->prev = prevNode;
		newNode->next = nowPos;
		nowPos->prev = newNode;
		
	}

	template<typename T>
	inline void List<T>::pop_back()
	{
		LinkedListBase<T>::pop_back();
	}

	template<typename T>
	inline void List<T>::pop_front()
	{
		LinkedListBase<T>::pop_front();
	}

	template<typename T>
	inline void List<T>::push_back(T& _data)
	{
		LinkedListBase<T>::push_back(_data);
	}

	template<typename T>
	inline void List<T>::push_front(T& _data)
	{
		LinkedListBase<T>::push_front(_data);
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
}