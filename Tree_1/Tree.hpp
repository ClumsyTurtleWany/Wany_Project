#pragma once

namespace TREE
{
	///////////////////////////////
	// node
	// depth: parent size
	// height: child depth
	enum class COLOR
	{
		RED,
		BLACK
	};

	template <typename K, typename T>
	class node
	{
	public:
		K key = K();
		T data = T();
		int depth = 0;
		int height = 0;
		bool isLeaf = true;
		COLOR color = COLOR::RED;
		node<K, T>* parent = nullptr;
		node<K, T>* child[2] = { nullptr, };

	public:
		node() {};
		~node() {};
	};

	////////////////////////////////////////////////////////////////////////////////////////
	// Red - Black Tree 규칙
	// 1. 신규 노드는 Red
	// 2. 삽입의 방법은 BST 알고리즘
	// 3. 모든 노드는 Red 혹은 Black 이여야 한다.
	// 4. 루트 노드는 반드시 Black 노드여야 한다.
	// 5. 모든 리프노드는 Black이다.
	// 6. 모든 Red 노드는 두 개의 Black 노드를 자식으로 갖는다. Red가 연속해서는 안됨.
	// 7. 모든 노드에서 리프노드까지의 Black 노드의 수는 동일 해야 한다.
	////////////////////////////////////////////////////////////////////////////////////////
	template <typename K, typename T>
	class RBT
	{
		using NODE = node<K, T>;
	private:
		NODE* root = nullptr;
		int degree = 0;
		int cnt = 0;
		int minKey = 0;
		int maxKey = 0;

	private:
		void insert(NODE* _node, NODE* _parent = nullptr);
		bool swap(NODE* _first, NODE* _second);
		node<K, T>* find(K _key, NODE* _parent);
		void flipColor(NODE* _target);
		void restruct(NODE* _target);
		void rotateLeft(NODE* _target);
		void rotateRight(NODE* _target);
		
	public:
		RBT() {};
		~RBT() {};

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

		void insert(K _key, T _data);

		//node<K, T>* find(K _key);
		T* find(K _key);
		
		iterator begin() { return iterator(find(minKey, root)); };
		iterator end() { return iterator(find(maxKey, root)); };

		int size() { return cnt; };

		void erase(NODE* _target);
		void erase(K _key);

	};

	template<typename K, typename T>
	inline void RBT<K, T>::insert(NODE* _node, NODE* _parent)
	{
		if (root == nullptr)
		{
			root = _node;
			minKey = _node->key;
			maxKey = _node->key;
			root->color = COLOR::BLACK;
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
					_parent->isLeaf = false;
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
					_parent->isLeaf = false;
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
	inline void RBT<K, T>::insert(K _key, T _data)
	{
		NODE* newNode = new NODE;
		newNode->key = _key;
		newNode->data = _data;
		insert(newNode, root);
		flipColor(newNode);
	}

	template<typename K, typename T>
	inline node<K, T>* RBT<K, T>::find(K _key, NODE* _parent)
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
	inline void RBT<K, T>::flipColor(NODE* _target)
	{
		if (_target == nullptr)
		{
			return;
		}
		else
		{
			NODE* parent = _target->parent;
			if (parent != nullptr)
			{
				if (parent->color == COLOR::RED)
				{
					NODE* grandParent = parent->parent;
					if (grandParent != nullptr)
					{
						NODE* uncle = grandParent->child[0] == parent ? grandParent->child[1] : grandParent->child[0];
						// Check Double Red
						if (uncle != nullptr)
						{
							if (uncle->color == COLOR::RED)
							{
								// Color
								uncle->color = COLOR::BLACK;
								parent->color = COLOR::BLACK;
								grandParent->color = COLOR::RED;
								flipColor(grandParent);
							}
							else
							{
								// Restruct
								restruct(_target);

							}
						}
						else
						{
							// Restruct
							restruct(_target);
						}
					}
				}
			}

			if (root != nullptr)
			{
				root->color = COLOR::BLACK;
			}
		}
	}

	template<typename K, typename T>
	inline void RBT<K, T>::restruct(NODE* _target)
	{
		if (_target == nullptr)
		{
			return;
		}
		else
		{
			NODE* parent = _target->parent;
			if (parent != nullptr)
			{
				NODE* grandParent = parent->parent;
				if (grandParent != nullptr)
				{
					if (grandParent->key > parent->key)
					{
						// gp->child[0] == parent
						if(parent->key > _target->key)
						{
							// gp   4 
							// p   3
							// t  2
							// RR Rotate
							NODE* GPP = grandParent->parent;
							if (GPP != nullptr)
							{
								if (GPP->child[0] == grandParent)
								{
									GPP->child[0] = parent;
									parent->parent = GPP;
									parent->child[1] = grandParent;
									grandParent->parent = parent;
								}
								else
								{
									GPP->child[1] = parent;
									parent->parent = GPP;
									parent->child[1] = grandParent;
									grandParent->parent = parent;
								}
							}
						}
						else
						{
							// gp   4 
							// p   2
							// t    3
							// LR Rotate(LL + RR)
							NODE* GPP = grandParent->parent;
							if (GPP != nullptr)
							{
								if (GPP->child[0] == grandParent)
								{
									GPP->child[0] = _target;
									_target->parent = GPP;
									_target->child[1] = grandParent;
									_target->child[0] = parent;
									parent->child[1] = nullptr;
									parent->parent = _target;
									grandParent->parent = _target;
								}
								else
								{
									GPP->child[1] = _target;
									_target->parent = GPP;
									_target->child[1] = grandParent;
									_target->child[0] = parent;
									parent->child[1] = nullptr;
									parent->parent = _target;
									grandParent->parent = _target;
								}
							}

							rotateLeft(_target);
						}
					}
					else if(grandParent->key < parent->key)
					{
						// gp->child[1] == parent
						if (parent->key < _target->key)
						{
							// gp   4 
							// p     5
							// t      6
							// LL Rotate

						}
						else
						{
							// gp   4 
							// p     6
							// t    5
							// RL Rotate(RR + LL)
						}
					}

				}
			}
		}
	}

	template<typename K, typename T>
	inline void RBT<K, T>::rotateLeft(NODE* _target)
	{
		if (_target == nullptr)
		{
			return;
		}
		else
		{
			NODE* parent = _target->parent;
			if (parent != nullptr)
			{
				if (parent->key < _target->key)
				{
					NODE* grandParent = parent->parent;
					if (grandParent != nullptr)
					{
						if (grandParent->key < parent->key)
						{
							// gp  4
							// p    5
							// t     6
							NODE* GPP = grandParent->parent;
							parent->child[0] = grandParent;
							
						}
						else
						{
							// gp    7
							// p    5
							// t     6
						}
					}
				}
			}
		}
	}

	template<typename K, typename T>
	inline void RBT<K, T>::rotateRight(NODE* _target)
	{
	}

	template<typename K, typename T>
	inline T* RBT<K, T>::find(K _key)
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
				NODE* rst = find(_key, temp->child[0]);
				return rst != nullptr ? rst->data : nullptr;
			}
			else if (_key > temp->key)
			{
				NODE* rst = find(_key, temp->child[1]);
				return rst != nullptr ? rst->data : nullptr;
			}
			else
			{
				return temp->data;
			}
		}
	}

	template<typename K, typename T>
	inline bool RBT<K, T>::swap(NODE* _first, NODE* _second)
	{
		if (_first != nullptr && _second != nullptr)
		{
			NODE temp = *_second;
			NODE* firstParent = _first->parent;
			NODE* firstChildLeft = _first->child[0];
			NODE* firstChildRight = _first->child[1];

			NODE* secondParent = _second->parent;
			NODE* secondChildLeft = _second->child[0];
			NODE* secondChildRight = _second->child[1];

			if (firstParent != nullptr)
			{
				if (firstParent->child[0] == _first)
				{
					firstParent->child[0] = _second;
				}
				else if (firstParent->child[1] == _first)
				{
					firstParent->child[1] = _second;
				}
			}
			else
			{
				root = _second;
			}

			if (firstChildLeft != nullptr)
			{
				firstChildLeft->parent = _second;
			}

			if (firstChildRight != nullptr)
			{
				firstChildRight->parent = _second;
			}

			if (firstParent != _second) // test
			{
				_second->parent = firstParent;
			}
			else
			{
				_second->parent = _first;
			}

			if (_second != _first->child[0])
			{
				_second->child[0] = _first->child[0];
			}
			else
			{
				_second->child[0] = _first;
			}

			if (_second != _first->child[1])
			{
				_second->child[1] = _first->child[1];
			}
			else
			{
				_second->child[1] = _first;
			}
			_second->depth = _first->depth;
			_second->height = _first->height;
			_second->isLeaf = _first->isLeaf;

			
			if (secondParent != nullptr)
			{
				if (secondParent->child[0] == _second)
				{
					secondParent->child[0] = _first;
				}
				else if (secondParent->child[1] == _second)
				{
					secondParent->child[1] = _first;
				}
			}
			else
			{
				root = _first;
			}

			if (secondChildLeft != nullptr)
			{
				secondChildLeft->parent = _first;
			}
			
			if (secondChildRight != nullptr)
			{
				secondChildRight->parent = _first;
			}
			
			if (temp.parent != _first) // test
			{
				_first->parent = temp.parent;
			}
			else
			{
				_first->parent = _second;
			}


			if (_first != temp.child[0])
			{
				_first->child[0] = temp.child[0];
			}
			else
			{
				_first->child[0] = &temp;
			}

			if (_first != temp.child[1])
			{
				_first->child[1] = temp.child[1];
			}
			else
			{
				_first->child[1] = &temp;
			}
			_first->depth = temp.depth;
			_first->height = temp.height;
			_first->isLeaf = temp.isLeaf;

			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename K, typename T>
	inline void RBT<K, T>::erase(NODE* _target)
	{
		// target->child[0]->child[1] 과 target 교환
		// 혹은 target->child[1]->child[0]과 교환
		// child[0] == nullptr && child[1] == nullptr 인 노드(leaf node)까지 target이 도달했을 때 target 삭제.
		// target->child[0]->child[1] 혹은 target->child[1]->child[0]이 없을 때,
		// target->child[0] 혹은 target->child[1] 와 swap하여 다시 탐색 반복.
		if (_target != nullptr)
		{
			if (_target->isLeaf)
			{
				delete _target;
				cnt--;
				return;
			}
			else
			{
				// search left
				NODE* targetChildLeft = _target->child[0];
				if (targetChildLeft != nullptr)
				{
					NODE* leafNode = targetChildLeft->child[1];
					if (leafNode != nullptr)
					{
						while (leafNode->child[1] != nullptr)
						{
							leafNode = leafNode->child[1];
						}

						swap(_target, leafNode);
						NODE* parent = _target->parent;
						if (parent->child[0] == _target)
						{
							parent->child[0] = nullptr;
						}
						else if (parent->child[1] == _target)
						{
							parent->child[1] = nullptr;
						}

						delete _target;
						if (parent != nullptr)
						{
							if ((parent->child[0] == nullptr) && (parent->child[1] == nullptr))
							{
								parent->isLeaf = true;
							}
						}

						cnt--;
						return;
					}
					else
					{
						swap(_target, targetChildLeft);
						erase(_target);
						return;
					}
				}

				// search right
				NODE* targetChildRight = _target->child[1];
				if (targetChildRight != nullptr)
				{
					NODE* leafNode = targetChildRight->child[0];
					if (leafNode != nullptr)
					{
						while (leafNode->child[0] != nullptr)
						{
							leafNode = leafNode->child[0];
						}

						swap(_target, leafNode);
						NODE* parent = _target->parent;
						if (parent->child[1] == _target)
						{
							parent->child[1] = nullptr;
						}
						else if (parent->child[0] == _target)
						{
							parent->child[0] = nullptr;
						}

						delete _target;
						if (parent != nullptr)
						{
							if ((parent->child[0] == nullptr) && (parent->child[1] == nullptr))
							{
								parent->isLeaf = true;
							}
						}

						cnt--;
						return;
					}
					else
					{
						swap(_target, targetChildRight);
						erase(_target);
						return;
					}
				}


			}

		}
	}

	template<typename K, typename T>
	inline void RBT<K, T>::erase(K _key)
	{
		NODE* target = find(_key, root);
		if(target == nullptr)
		{
			return;
		}
		else
		{
			erase(target);
			return;
		}
	}
}
