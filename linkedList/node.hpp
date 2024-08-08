#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <utility>

#include <iostream>

namespace my
{
	template <typename T>
	struct Node
	{
		Node(T&&);
		Node(T&&, Node*);
		Node(const Node&);
		Node(Node&&);
		~Node() = default;

		Node&	operator= (const Node&);
		Node&	operator= (Node&&);

		void	display();

		T	_data;
		Node*	_next;
	};

	template<typename T>
	Node<T>::Node(T&& data) : _data(std::forward<T>(data)), _next(nullptr) {}

	template<typename T>
	Node<T>::Node(const Node& oldNode) : _data(oldNode._data), _next(oldNode._next) {}

	template<typename T>
	Node<T>::Node(Node&& oldNode) : _data(oldNode._data), _next(oldNode._next)
	{ oldNode._next = nullptr; }

	template<typename T>
	Node<T>&	Node<T>::operator= (const Node& oldNode)
	{
		if (this != &oldNode)
		{
			_data = oldNode._data;
			_next = oldNode._next;
		}
		return *this;
	}

	template<typename T>
	Node<T>& Node<T>::operator= (Node&& oldNode)
	{
		if (this != &oldNode) {
			_data = std::move(oldNode._data);
			_next = oldNode._next;
			oldNode._next = nullptr;
		}
		return *this;
	}

	template<typename T>
	Node<T>::Node(T&& data, Node* next) : _data(std::forward<T>(data)), _next(next) {}

	template<typename T>
	void Node<T>::display()
	{
		std::cout << _data;
		if(_next)
			std::cout << " -> ";
		else
			std::cout << std::endl;
	}
}
#endif // __NODE_HPP__
