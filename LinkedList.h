#pragma once
#include <iterator>

template <typename T>
class LinkedList
{
public:
	class ListNode
	{
	public:
		ListNode(T value) :_value(value)
		{
			_prev = this;
			_next = this;
		}
		ListNode(T value, ListNode* prev, ListNode* next)
			:_value(value), _prev(prev), _next(next)
		{
			_prev->_next = this;
			_next->_prev = this;
		}
		~ListNode()
		{
			_prev->_next = _next;
			_next->_prev = _prev;
		}

		T _value;
		ListNode* _next;
		ListNode* _prev;
	};

	class iterator : std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		iterator(ListNode* node, ListNode* listHead) : _node(node), _listHead(listHead) {}
		iterator& operator++()
		{
			if (_node == _listHead)
				throw std::runtime_error("end of list");
			_node = _node->_next;
			return *this;
		}
		iterator operator++(int unused)
		{
			if (_node == _listHead)
				throw std::runtime_error("end of list");
			iterator copy(*this);
			_node = _node->_next;
			return copy;
		}
		iterator& operator--()
		{
			if (_node == _listHead->_next)
				throw std::runtime_error("begin of list");
			_node = _node->_prev;
			return *this;
		}
		iterator operator--(int unused)
		{
			if (_node == _listHead->_next)
				throw std::runtime_error("begin of list");
			iterator copy(*this);
			_node = _node->_prev;
			return copy;
		}
		T& operator*() const
		{
			return _node->_value;
		}
		T* operator->() const
		{
			return &_node->_value;
		}
		bool operator==(const iterator& other) const
		{
			return _node == other._node;
		}
		bool operator!=(const iterator& other) const
		{
			return !(*this == other);
		}
		
		ListNode* _node;
		ListNode* _listHead;
	};

	class const_iterator : std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		const_iterator(ListNode* node) : _node(node) {}
		const_iterator& operator++()
		{//preincr
			_node = _node->_next;
			return *this;
		}
		const_iterator operator++(int unused)
		{
			const_iterator copy(*this);
			_node = _node->_next;
			return copy;
		}
		const_iterator& operator--()
		{//predecr
			_node = _node->_prev;
			return *this;
		}
		const_iterator operator--(int unused)
		{//postdecr
			const_iterator copy(*this);
			_node = _node->_prev;
			return copy;
		}
		T& operator*() const
		{
			return _node->_value;
		}
		T* operator->() const
		{
			return &_node->_value;
		}
		bool operator==(const const_iterator& other) const
		{
			return _node == other._node;
		}
		bool operator!=(const const_iterator& other) const
		{
			return !(*this == other);
		}

		ListNode* _node;
		ListNode* _listHead;
	};

	class reverse_iterator : std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		reverse_iterator(ListNode* node) : _node(node) {}
		reverse_iterator& operator++()
		{
			_node = _node->_prev;
			return *this;
		}
		reverse_iterator operator++(int unused)
		{
			reverse_iterator copy(*this);
			_node = _node->_prev;
			return copy;
		}
		reverse_iterator& operator--()
		{
			_node = _node->_next;
			return *this;
		}
		reverse_iterator operator--(int unused)
		{
			reverse_iterator copy(*this);
			_node = _node->_next;
			return copy;
		}
		T& operator*() const
		{
			return _node->_value;
		}
		T* operator->() const
		{
			return &_node->_value;
		}
		bool operator==(const reverse_iterator& other) const
		{
			return _node == other._node;
		}
		bool operator!=(const reverse_iterator& other) const
		{
			return !(*this == other);
		}

		ListNode* _node;
	};

	class const_reverse_iterator : std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		const_reverse_iterator(ListNode* node) : _node(node) {}
		const_reverse_iterator& operator++()
		{
			_node = _node->_prev;
			return *this;
		}
		const_reverse_iterator operator++(int unused)
		{
			const_reverse_iterator copy(*this);
			_node = _node->_prev;
			return copy;
		}
		const_reverse_iterator& operator--()
		{
			_node = _node->_next;
			return *this;
		}
		const_reverse_iterator operator--(int unused)
		{
			iterator copy(*this);
			_node = _node->_next;
			return copy;
		}
		T& operator*() const
		{
			return _node->_value;
		}
		T* operator->() const
		{
			return &_node->_value;
		}
		bool operator==(const const_reverse_iterator& other) const
		{
			return _node == other._node;
		}
		bool operator!=(const const_reverse_iterator& other) const
		{
			return !(*this == other);
		}

		ListNode* _node;
	};


	LinkedList()
		:_head(new ListNode(T())) {}

	LinkedList(const LinkedList<T>& right);
	LinkedList(LinkedList<T>&& right);
	LinkedList<T>& operator=(LinkedList<T>& right);
	LinkedList<T>& operator=(LinkedList<T>&& right);
	void clear();
	bool empty() const;
	void insert(iterator where, const T& value)
	{
		new ListNode(value, where._node->_prev, where._node);
	}
	void push_front(const T& value);
	void erase(iterator where)
	{
		where._node = where._node->_next;
		new ListNode(*(where), where._node->_prev->_prev, where._node->_next);
		delete where._node;
	}
	void remove(T value);
	void reverse();
	T Get(int position);
	const T Get(int jposition) const;
	void push_back(T value);

	iterator begin() { return iterator(_head->_next, _head); }
	const_iterator begin() const { return const_iterator(_head->_next); }
	reverse_iterator rbegin() { return reverse_iterator(_head->_prev); }
	const_reverse_iterator rbegin() const { ListNode* temp = _head->_prev; return const_reverse_iterator(temp); }

	iterator end() { return iterator(_head, _head); }
	const_iterator end() const { return const_iterator(_head); }
	reverse_iterator rend() { return reverse_iterator(_head); }
	const_reverse_iterator rend() const { return const_reverse_iterator(_head); }
private:
	ListNode* _head;
};

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& right)
{
	_head = right._head;
	push_back(_head->_value);
	ListNode* end = right._head;
	ListNode* cp = right._head->_next;
	while (cp->_value != end->_value)
	{
		push_back(cp->_value);
		cp = cp->_next;
	}
}

template<typename T>
inline LinkedList<T>::LinkedList(LinkedList<T>&& right)
{
	this->clear();
	_head = right._head;
	push_back(_head->_value);
	ListNode* end = right._head;
	ListNode* cp = right._head->_next;
	while (cp->_value != end->_value)
	{
		push_back(cp->_value);
		cp = cp->_next;
	}
	right->clear();
}

template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& right)
{
	if (_head == right._head)
		return *this;
	this->clear();
	_head = right._head;
	push_back(_head->_value);
	ListNode* end = right._head;
	ListNode* cp = right._head->_next;
	while (cp->_value != end->_value)
	{
		push_back(cp->_value);
		cp = cp->_next;
	}
	return *this;
}

template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& right)
{
	if (_head == right._head)
		return *this;
	this->clear();
	_head = right._head;
	push_back(_head->_value);
	ListNode* end = right._head;
	ListNode* cp = right._head->_next;
	while (cp->_value != end->_value)
	{
		push_back(cp->_value);
		cp = cp->_next;
	}
	right->clear();
	return *this;
}

template<typename T>
inline void LinkedList<T>::clear()
{
	while (_head != _head->_prev)
	{
		ListNode* remover = _head;
		remover = remover->_next;
		delete remover;
	}
	_head = nullptr;
}

template<typename T>
inline bool LinkedList<T>::empty() const
{
	if (_head != nullptr)
		return false;
	return true;
}



template<typename T>
inline void LinkedList<T>::push_front(const T & value)
{
	ListNode* afterHead = _head->_next;
	iterator after(afterHead, _head);
	insert(after, value);
}

template<typename T>
inline void LinkedList<T>::remove(T value)
{
	for (auto it = begin(); it != end(); ++it)
	{
		if (*it == value)
			erase(it);
	}
}

template<typename T>
inline void LinkedList<T>::reverse()
{
	ListNode* _Phead = _head;
	ListNode* _Pnode = _Phead;

	for (;;)
	{
		ListNode* _Pnext = _Pnode->_next;
		_Pnode->_next = _Pnode->_prev;
		_Pnode->_prev = _Pnext;

		if (_Pnext == _Phead)
			break;
		_Pnode = _Pnext;
	}
}

template<typename T>
inline T LinkedList<T>::Get(int position)
{
	ListNode* list = _head->_next;
	for (int i = 0; i < position; ++i)
	{
		list = list->_next;
	}
	return list->_value;
}

template<typename T>
inline const T LinkedList<T>::Get(int jposition) const
{
	ListNode* list = _head->_next;
	for (int i = 0; i < jposition; ++i)
	{
		list = list->_next;
	}
	return list->_value;
}

template<typename T>
inline void LinkedList<T>::push_back(T value)
{
	ListNode * newNode = new ListNode(value, _head->_prev, _head);
}