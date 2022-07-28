#pragma once

namespace TREE
{
	///////////////////////////////
	// node
	// depth: parent size
	// height: child depth
	template <typename T>
	struct node
	{
		T data = T();
		int depth = 0;
		int index = 0;
		int height = 0;
		node<T>* parent = nullptr;
		node<T>* child[2] = { nullptr, };
	};

	template <typename T>
	class Tree
	{
	private:
		node<T>* root = nullptr;
		int degree = 0;
		int size = 0;

	public:
		Tree() {};
		~Tree() {};

		class iterator
		{
		private:
			node<T>* cur;
		public:
			iterator(node<T>* _data = nullptr) : cur(_data) {};
			~iterator() {};

			iterator& operator++()
			{
				if (cur->child[1] != nullptr)
				{
					if (cur->data < cur->child[1]->data)
					{
						node<T>* temp = cur->child[1];
						while (temp->child[0] != nullptr)
						{
							temp = temp->child[0];
						}

						cur = temp;
						return *this;
					}
				}

				if (cur->child[1] == nullptr)
				{
					if (cur->data < cur->parent->data)
					{
						cur = cur->parent;
						return *this;
					}
					else
					{
						node<T>* temp = cur->parent;
						while (temp->data < cur->data)
						{
							if (temp->parent != nullptr)
							{
								temp = temp->parent;
							}
							else
							{
								temp = nullptr;
								break;
							}
						}
						cur = temp;					
						return *this;
					}
				}
			}

			iterator operator++(int)
			{
				iterator temp = *this;
				++* this;
				return temp;
			}

			iterator& operator--()
			{
				if (cur->child[0] != nullptr)
				{
					if (cur->child[0]->data < cur->data)
					{
						cur = cur->child[0];
						return *this;
					}
				}

				if (cur->child[0] == nullptr)
				{
					if (cur->parent->data < cur->data)
					{
						cur = cur->parent;
						return *this;
					}
					else
					{
						node<T>* temp = cur->parent;
						while (cur->data < temp->data)
						{
							if (temp->parent != nullptr)
							{
								temp = temp->parent;
							}
							else
							{
								temp = nullptr;
								break;
							}
						}
						cur = temp;
						return *this;
					}
				}
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

		void insert(T _data, node<T>* _parent = nullptr);
		iterator find(T _data, node<T>* _parent = nullptr)
		{
			if (root == nullptr)
			{
				return iterator(nullptr);
			}
			else
			{
				if (_parent == nullptr)
				{
					_parent = root;
				}

				if (_data < _parent->data)
				{
					return find(_data, _parent->child[0]);
				}
				else if (_data > _parent->data)
				{
					return find(_data, _parent->child[1]);
				}
				else
				{
					return iterator(_parent);
				}
			}
		}

		void erase(TREE::Tree<T>::iterator _iter);

	};

	template<typename T>
	inline void Tree<T>::insert(T _data, node<T>* _parent)
	{
		if (root == nullptr)
		{
			root = new node<T>;
			root->data = _data;
			size++;
		}
		else
		{
			if (_parent == nullptr)
			{
				_parent = root;
			}

			if (_data < _parent->data)
			{
				if (_parent->child[0] == nullptr)
				{
					_parent->child[0] = new node<T>;
					_parent->child[0]->parent = _parent;
					_parent->child[0]->data = _data;
					_parent->child[0]->depth = _parent->depth + 1;
					size++;
				}
				else
				{
					insert(_data, _parent->child[0]);
				}
			}
			else if(_data > _parent->data)
			{
				if (_parent->child[1] == nullptr)
				{
					_parent->child[1] = new node<T>;
					_parent->child[1]->parent = _parent;
					_parent->child[1]->data = _data;
					_parent->child[1]->depth = _parent->depth + 1;
					size++;
				}
				else
				{
					insert(_data, _parent->child[1]);
				}
			}
			else
			{
				_parent->data = _data;
			}
		}
	}

	template<typename T>
	inline void Tree<T>::erase(TREE::Tree<T>::iterator _iter)
	{
		
	}
}
