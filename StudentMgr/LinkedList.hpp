#pragma once

namespace LL
{
	template <typename T>
	struct node
	{
		T		data;
		node*	prev;
		node*	next;
	};

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	// 
	// Linked List Base Class
	// 
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	template <typename T>
	class LinkedListBase
	{
		private:
		public:

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
		head = new node<T>;
		tail = new node<T>;
		head->next = tail;
		tail->prev = head;
		dataSize = 0;
	}

	template<typename T>
	inline LinkedListBase<T>::~LinkedListBase()
	{
		release();
		delete[] head;
		delete[] tail;
	}

	template<typename T>
	inline void LinkedListBase<T>::push_front(T& _data)
	{
		node<T>* newNode = new node<T>;
		newNode->data = _data;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		node<T>* tempNode = head->next; // == tail
		tempNode->prev = newNode;
		newNode->next = tempNode; // newNode->next = tail
		newNode->prev = head;
		head->next = newNode;
		

		
		dataSize++;
	}

	template<typename T>
	inline void LinkedListBase<T>::push_back(T& _data)
	{
		node<T>* newNode = new node<T>;
		newNode->data = _data;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		node<T>* tempNode = tail->prev; // == tail
		tempNode->next = newNode;
		newNode->prev = tempNode;
		newNode->next = tail;
		tail->prev = newNode;

		// push_front
		//node<T>* tempNode = head->next; // == tail
		//tempNode->prev = newNode;
		//newNode->next = tempNode; // newNode->next = tail
		//newNode->prev = head;
		//head->next = newNode;

		dataSize++;
	}

	template<typename T>
	inline void LinkedListBase<T>::pop_back()
	{
		node<T>* curNode = tail->prev;
		node<T>* prevNode = curNode->prev;
		tail->prev = prevNode;
		prevNode->next = tail;
		delete[] curNode;
		dataSize--;
	}

	template<typename T>
	inline void LinkedListBase<T>::pop_front()
	{
		node<T>* curNode = head->next;
		node<T>* nextNode = curNode->next;
		head->next = nextNode;
		nextNode->prev = head;
		delete[] curNode;
		dataSize--;
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
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	template <typename T>
	class Stack : public LinkedListBase<T>
	{
		private:
		public:
			Stack() {};
			~Stack() {};
			T& top() 
			{ 
				node<T>* curNode = LinkedListBase<T>::tail->prev;
				return curNode->data; 
			};
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
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	template <typename T>
	class Queue : public LinkedListBase<T>
	{
	private:
	public:
		Queue() {};
		~Queue() {};
		T& front() 
		{ 
			node<T>* curNode = LinkedListBase<T>::head->next;
			return curNode->data; 
		};
		T& back() 
		{ 
			node<T>* curNode = LinkedListBase<T>::tail->prev;
			return curNode->data; 
		};
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
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
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

					/*bool operator !=(iterator& _cmp)
					{
						return (cur != _cmp.cur);
					}*/

					bool operator !=(iterator _cmp)
					{
						return (cur != _cmp.cur);
					}

					bool operator ==(iterator& _cmp)
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
			iterator begin() {	return iterator(LinkedListBase<T>::head->next); }

			// -cbegin: return const iterator of first element.
			const iterator cbegin() { return iterator(LinkedListBase<T>::head->next); }

			// end: return iterator of last element.
			iterator end() { return iterator(LinkedListBase<T>::tail); }
		
			// -cend: return const iterator of last element.
			const iterator cend() { return iterator(LinkedListBase<T>::tail); }
		
			// -clear: delete all element.
			void clear();

			
		
			

			// -erase: delete element or delete element of selected area.
			void erase(iterator _iter);
			void erase(iterator _first, iterator _last);

			// -front: return first element.
			T& front();
			
			// -get_allocator: return copy of allocator.
		
			// insert: insert element or insert elements of selected area.
			void insert(iterator _iter, T& _data);

			

			// merge: delete element and insert element to list, sort asec, desc, etc.
		
			// pop_back: delete last element.
			void pop_back();

			// pop_front: delete first element.
			void pop_front();

			// push_back: insert element at last.
			void push_back(T& _data);

			// push_front: insert element at first.
			void push_front(T& _data);		 


			// empty: return true or false.
			// size: return element amount.
			// -emplace: insert element.
			
			// max_size: return maximum list length. (Max allocate count)
			// rbegin: return reversed iterator of first element. (= end)
			// resize: resize.
			// reverse: reverse list.
			// sort: sort asec, desc, etc.
			// splice: delete element and insert element at other list.
			// swap: swap elements with other list.
			// unique: delete same element.
			// -crbegin: return reversed const iterator of first element. (= cend)
			// -crend : return reversed const iterator of last element. (= cbegin)

			
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
			LinkedListBase<T>::push_back(_data);
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
		node<T>* curNode = LinkedListBase<T>::tail->prev;
		return curNode->data;
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
	inline void List<T>::erase(iterator _iter)
	{
		node<T>* selectedNode = &_iter;
		node<T>* prevNode = selectedNode->prev;
		node<T>* nextNode = selectedNode->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		delete[] selectedNode;
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
			delete[] deleteNode;
		}
	}

	template<typename T>
	inline T& List<T>::front()
	{
		node<T>* curNode = LinkedListBase<T>::head->next;
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