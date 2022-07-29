#pragma once

namespace TREE
{
	///////////////////////////////
	// node
	// depth: parent size
	// height: child depth
	template <typename K, typename T>
	struct node
	{
		K key = K();
		T data = T();
		int depth = 0;
		int height = 0;
		node<K, T>* parent = nullptr;
		node<K, T>* child[2] = { nullptr, };
	};

	template <typename K, typename T>
	class BST
	{
		using NODE = node<K, T>;
	private:
		NODE* root = nullptr;
		int degree = 0;
		int cnt = 0;
		int minKey = 0;
		int maxKey = 0;

		
		
	public:
		BST() {};
		~BST() {};

		class iterator
		{
		private:
			NODE* cur;
		public:
			iterator(NODE* _data = nullptr) : cur(_data) {};
			~iterator() {};

			iterator& operator++()
			{
				if (cur->child[1] != nullptr)
				{
					if (cur->key < cur->child[1]->key)
					{
						NODE* temp = cur->child[1];
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
					if (cur->key < cur->parent->key)
					{
						cur = cur->parent;
						return *this;
					}
					else
					{
						NODE* temp = cur->parent;
						while (temp->key < cur->key)
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
					if (cur->child[0]->key < cur->key)
					{
						NODE* temp = cur->child[0];
						while (temp->child[1] != nullptr)
						{
							temp = temp->child[1];
						}
						cur = temp;
						return *this;
					}
				}

				if (cur->child[0] == nullptr)
				{
					if (cur->parent->key < cur->key)
					{
						cur = cur->parent;
						return *this;
					}
					else
					{
						NODE* temp = cur->parent;
						while (cur->key < temp->key)
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

			NODE* operator&()
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

		void insert(NODE* _node, NODE* _parent = nullptr);
		void insert(K _key, T _data);

		node<K, T>* find(K _key);
		node<K, T>* find(K _key, NODE* _parent);
		
		iterator begin() { return iterator(find(minKey)); };
		iterator end() { return iterator(find(maxKey)); };

		bool swap(NODE* _first, NODE* _second);

		int size() { return cnt; };

		void erase(iterator _iter);
		void erase(K _key);

	};

	template<typename K, typename T>
	inline void BST<K, T>::insert(NODE* _node, NODE* _parent)
	{
		if (root == nullptr)
		{
			root = _node;
			minKey = _node->key;
			maxKey = _node->key;
			cnt++;
		}
		else
		{
			if (_parent == nullptr)
			{
				_parent = root;
			}

			if (_node->key < _parent->key)
			{
				if (_parent->child[0] == nullptr)
				{
					_node->parent = _parent;
					_node->depth = _parent->depth + 1;
					_parent->child[0] = _node;
					minKey = minKey < _node->key ? minKey : _node->key;
					maxKey = maxKey < _node->key ? _node->key : maxKey;
					cnt++;
				}
				else
				{
					insert(_node, _parent->child[0]);
				}
			}
			else if(_node->key > _parent->key)
			{
				if (_parent->child[1] == nullptr)
				{
					_node->parent = _parent;
					_node->depth = _parent->depth + 1;
					_parent->child[1] = _node;
					minKey = minKey < _node->key ? minKey : _node->key;
					maxKey = maxKey < _node->key ? _node->key : maxKey;
					cnt++;
				}
				else
				{
					insert(_node, _parent->child[1]);
				}
			}
			else
			{
				_parent->key = _node->key;
				_parent->data = _node->data;
				minKey = minKey < _node->key ? minKey : _node->key;
				maxKey = maxKey < _node->key ? _node->key : maxKey;
			}
		}
	}

	template<typename K, typename T>
	inline void BST<K, T>::insert(K _key, T _data)
	{
		NODE* newNode = new NODE;
		newNode->key = _key;
		newNode->data = _data;
		insert(newNode, root);
	}

	template<typename K, typename T>
	inline node<K, T>* BST<K, T>::find(K _key, NODE* _parent)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		else
		{
			if (_parent == nullptr)
			{
				_parent = root;
			}

			if (_key < _parent->key)
			{
				return find(_key, _parent->child[0]);
			}
			else if (_key > _parent->key)
			{
				return find(_key, _parent->child[1]);
			}
			else
			{
				return _parent;
			}
		}
	}
	
	template<typename K, typename T>
	inline node<K, T>* BST<K, T>::find(K _key)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		else
		{
			NODE* temp = root;
			if (_key < temp->key)
			{
				return find(_key, temp->child[0]);
			}
			else if (_key > temp->key)
			{
				return find(_key, temp->child[1]);
			}
			else
			{
				return temp;
			}
		}
	}

	template<typename K, typename T>
	inline bool BST<K, T>::swap(NODE* _first, NODE* _second)
	{
		if (_first != nullptr && _second != nullptr)
		{
			
			NODE temp = *_first;
			NODE* firstParent = _first->parent;
			NODE* firstChildLeft = _first->child[0];
			NODE* firstChildRight = _first->child[1];

			NODE* secondParent = _second->parent;
			NODE* secondChildLeft = _second->child[0];
			NODE* secondChildRight = _second->child[1];
			
			if (firstParent->child[0] == _first)
			{
				firstParent->child[0] = _second;
			}
			else if (firstParent->child[1] == _first)
			{
				firstParent->child[1] = _second;
			}

			if (secondParent->child[0] == _second)
			{
				secondParent->child[0] = _first;
			}
			else if (secondParent->child[1] == _second)
			{
				secondParent->child[1] = _first;
			}

			if (secondChildLeft == nullptr)
			{

			}

			/*template < class K, class T>
			void	TTable<K, T>::erase(K k)
			{
				m_pBstRoot = removeBst(k, m_pBstRoot);
			}
			template < class K, class T>
			TBstNode<K, T>* TTable<K, T>::removeBst(K k, TBstNode<K, T>*t)
			{
				TBstNode<K, T>* temp;
				if (t == NULL)
				{
					return NULL;
				}
				else if (k < t->m_key)
				{
					t->m_pChild[0] = removeBst(k, t->m_pChild[0]);
				}
				else if (k > t->m_key)
				{
					t->m_pChild[1] = removeBst(k, t->m_pChild[1]);
				}
				else if (t->m_pChild[0] && t->m_pChild[1])
				{
					temp = findMin(t->m_pChild[1]);
					t->m_key = temp->m_key;
					t->m_pChild[1] = removeBst(t->m_key, t->m_pChild[1]);
				}
				else
				{
					temp = t;
					if (t->m_pChild[0] == NULL)
						t = t->m_pChild[1];
					else if (t->m_pChild[1] == NULL)
						t = t->m_pChild[0];
					delete temp;
				}
				return t;
			}*/

			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename K, typename T>
	inline void BST<K, T>::erase(TREE::BST<K, T>::iterator _iter)
	{
		
	}

	template<typename K, typename T>
	inline void BST<K, T>::erase(K _key)
	{
		// target->child[0]->child[1] 과 target 교환
		// 혹은 target->child[1]->child[0]과 교환
		// child[0] == nullptr && child[1] == nullptr 인 노드까지 target이 도달했을 떄
		// target 삭제.

		NODE* target = find(_key);
		if (target != nullptr)
		{
			int a = 0;
			swap(target, root);

			



		}
	}
}
