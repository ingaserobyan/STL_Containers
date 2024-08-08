#ifndef __SINGLE_LIST_H__
#define __SINGLE_LIST_H__

#include "node.hpp"

namespace my
{
	template <typename T>
	class singleList
	{
		public:
			singleList();
			singleList(T&&);
			singleList(Node<T>&);
			~singleList();

		public:
			void	push_front(const Node<T>&);
			void	push_front(T&&);
			void	pop_front();
			void	insert(T&&, const int&);
			void	insert(Node<T>&, const int&);

		public:
			T	average();
			Node<T>*	findLastN(T&&);
			void	reverse();
			bool	isCyclic();
			void	display();

		public:
			template<typename U>
			class Iterator
			{
				public:
					Iterator(Node<U>*);

					Node<U>&	operator*();
					Node<U>*	operator->();
					Iterator<U>&	operator++();
					Iterator<U>	operator++(int);
					bool	operator==(const Iterator<U>&) const;
					bool	operator!=(const Iterator<U>&) const;

				private:
					Node<U>* _current;
			};

		public:
			Iterator<T>	begin();
			Iterator<T>	end();
			void	pop(Iterator<T>& itr);

		private:
			Node<T>*	_head = nullptr;
	};

	template<typename T>
	singleList<T>::singleList() {}

	template<typename T>
	singleList<T>::singleList(T&& data) : _head(new Node<T>(std::move(data))) {}

	template<typename T>
	singleList<T>::singleList(Node<T>& myNode) : _head(new Node<T>(myNode)) {}

	template<typename T>
	singleList<T>::~singleList()
	{
		Node<T>*	tmp = nullptr;

		while(_head)
		{
			tmp = _head->_next;
			delete(_head);
			_head = tmp;
		}

	}

	template<typename T>
	void	singleList<T>::push_front(const Node<T>& element)
	{
		Node<T>* tmp = _head;
		_head = new Node<T>(element);
		_head->_next = tmp;
	}

	template<typename T>
	void	singleList<T>::push_front(T&& data)
	{
		Node<T>* tmp = _head;
		_head = new Node<T>(std::move(data));
		_head->_next = tmp;
	}

	template<typename T>
	void	singleList<T>::pop_front()
	{
		if (_head)
		{
			Node<T>* tmp = _head;
			_head = _head->_next;
			delete tmp;
		}
	}

	template<typename T>
	void	singleList<T>::display()
	{
		Node<T>* tmp = _head;
		while(tmp)
		{
			tmp->display();
			tmp = tmp->_next;
		}
	}

	template<typename T>
	void	singleList<T>::insert(T&& data, const int& position)
	{
		if(position <= 0)
		{
			this->push_front(std::move(data));
			return ;
		}

		Node<T>* tmp = _head;
		int	i = 0;

		while(i < (position - 1) && tmp)
		{
			++i;
			tmp = tmp->_next;
		}
		if(!tmp)
			return ;
		tmp->_next = new Node<T>(std::move(data), tmp->_next);
	}

	template<typename T>
	void	singleList<T>::insert(Node<T>& node, const int& position)
	{
		if(position <= 0)
		{
			this->push_front(node);
			return ;
		}

		Node<T>* tmp = _head;
		int	i = 0;

		while(i < (position - 1) && tmp)
		{
			++i;
			tmp = tmp->_next;
		}
		if(!tmp)
			return ;
		Node<T>* holder = tmp->_next;
		tmp->_next = new Node<T>(node);
		tmp->_next->_next = holder;
	}

	template<typename T>
	T singleList<T>::average()
	{
		T	avg = begin()->_data;
		int	count = 1;


		for(singleList<T>::Iterator<T> it = begin()->_next; it != end(); ++it)
		{
			avg += it->_data;
			count++;
		}
		if (count > 0)
			return (avg / count);
		else
			return 0;
	}

	template<typename T>
	Node<T>*	singleList<T>::findLastN(T&& value)
	{
		Node<T>*	counter = _head;
		Node<T>*	element = NULL;
		while(counter)
		{
			if(counter->_data == value)
				element = counter;
			counter = counter->_next;
		}
		return element;
	}

	template<typename T>
	void	singleList<T>::reverse()
	{
		Node<T>*	current = _head;
		Node<T>*	next = nullptr;
		Node<T>*	previous = nullptr;

		while(current)
		{
			next = current->_next;
			current->_next = previous;
			previous = current;
			current = next;
		}
		_head = previous;
	}

	template<typename T>
	bool	singleList<T>::isCyclic()
	{
		bool		status = false;
		Node<T>*	counter = _head;

		while(counter && (counter != _head))
		{
			if(counter->_next == _head)
				status = true;
			counter = counter->_next;
		}
		return status;
	}

	template<typename T>
	template<typename U>
	singleList<T>::Iterator<U>::Iterator(Node<U>* current) : _current(current) {}

	template<typename T>
	template<typename U>
	Node<U>& singleList<T>::Iterator<U>::operator* () {return *(_current);}

	template<typename T>
	template<typename U>
	Node<U>* singleList<T>::Iterator<U>::operator-> () {return _current;}

	template<typename T>
	template<typename U>
	typename singleList<T>::template Iterator<U>&	singleList<T>::Iterator<U>::operator++ ()
	{
		if (_current)
			_current = _current->_next;
		return *this;
	}

	template<typename T>
	template<typename U>
	typename singleList<T>::template Iterator<U>	singleList<T>::Iterator<U>::operator++(int)
	{
		Iterator<U> temp = *this;
		++(*this);
		return temp;
	}

	template<typename T>
	template<typename U>
	bool	singleList<T>::Iterator<U>::operator==(const Iterator<U>& other) const
	{
		return (_current == other._current);
	}

	template<typename T>
	template<typename U>
	bool	singleList<T>::Iterator<U>::operator!=(const Iterator<U>& other) const
	{
		return (_current != other._current);
	}

	template <typename T>
    typename singleList<T>::template Iterator<T>	singleList<T>::begin()
    {
        return Iterator<T>(_head);
    }


	template <typename T>
    typename singleList<T>::template Iterator<T>	singleList<T>::end()
    {
        return Iterator<T>(nullptr);
    }

	template <typename T>
	void singleList<T>::pop(singleList<T>::Iterator<T>& itr)
	{
		if (_head == nullptr)
			return;

		if (itr == end())
			return;

		if (itr == begin())
		{
			pop_front();
			itr = begin();
			return;
		}

		Iterator<T> previous = begin();
		while (previous != end() && previous->_next != &(*itr))
		{
			++previous;
		}

		if (previous != end())
		{
			previous->_next = itr->_next;
			delete &(*itr);
			itr = previous;
		}
	}
} // my

#endif // __SINGLE_LIST_H__
