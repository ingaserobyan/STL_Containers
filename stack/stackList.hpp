#ifndef __STACK_LST_H__
#define __STACK_LST_H__

#include "../linkedList/singleList.hpp"
#include "../linkedList/node.hpp"

template<typename T>
class Stack_lst
{
	public:
		Stack_lst();
		Stack_lst(const Stack_lst&);
		~Stack_lst();

	public:
		Stack_lst<T>&	operator=(const Stack_lst&);
		void	push(const T&);
		void	pop();
		T&		back() const;

	private:
		my::singleList<T>* _head = nullptr;
};

template<typename T>
Stack_lst<T>::Stack_lst() : _head(nullptr) {}

template<typename T>
Stack_lst<T>::Stack_lst(const Stack_lst& other)
{
	if(other._head)
	{
		_head = new my::singleList<T>(*(other._head));
	}
}

template<typename T>
Stack_lst<T>::~Stack_lst()
{
	delete _head;
}

template<typename T>
void	Stack_lst<T>::push(const T&	element)
{
	if (!_head)
		_head = new my::singleList<T>;
	_head->push_front(new my::Node<T>(element));
}

template<typename T>
void	Stack_lst<T>::pop()
{
	_head->pop_front();
}

template<typename T>
T&	Stack_lst<T>::back() const
{
	return _head->begin();
}

template<typename T>
Stack_lst<T>& Stack_lst<T>::operator=(const Stack_lst<T>& other)
{
	if (*this != *other)
	{
		delete _head;
		_head = nullptr;
		if(other._head)
		{
			_head = new my::singleList<T>(*(other._head));
		}
	}
	return this;
}
#endif // __STACK_LST_H__