#ifndef __STACK_VECTOR_H__
#define __STACK_VECTOR_H__

#include "../vector/vector.hpp"

template<typename T>
class Stack_Vec
{
	public:
		Stack_Vec();
		Stack_Vec(const Stack_Vec<T>&);
		~Stack_Vec();

	public:
		Stack_Vec<T>&	operator=(const Stack_Vec<T>&);
		void	push(const T&	element);
		void	pop();
		T&		back() const;

	private:
		my::Vector<T>* _vec = nullptr;
};

template<typename T>
Stack_Vec<T>::Stack_Vec() : _vec(nullptr) {}

template<typename T>
Stack_Vec<T>::Stack_Vec(const Stack_Vec& other)
{
	this->_vec = new my::Vector<T>;
	for(auto it : *(other._vec))
	{
		this->_vec->push_back(it);
	}
}

template<typename T>
Stack_Vec<T>::~Stack_Vec()
{
	delete _vec;
}

template<typename T>
void	Stack_Vec<T>::push(const T& element)
{
	if (!_vec)
	{
		_vec = new my::Vector<T>;
	}
	_vec->push_back(element);
}

template<typename T>
void	Stack_Vec<T>::pop()
{
	if (_vec)
	{
		_vec->pop_back();
	}
}

template<typename T>
T&	Stack_Vec<T>::back() const
{
	return(*(--(_vec->end())));
}

template<typename T>
Stack_Vec<T>& Stack_Vec<T>::operator=(const Stack_Vec<T>& other)
{
	if (this != &other)
	{
		delete this->_vec;
		this->_vec = new my::Vector<T>;
		for(auto it : *(other._vec))
		{
			this->_vec->push_back(it);
		}
	}
	return this;
}

#endif // __STACK_VECTOR_H__