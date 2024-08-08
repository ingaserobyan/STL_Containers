#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <cstddef>
#include <initializer_list>

namespace my
{
	template <typename T>
	class Vector
	{
		public:
			Vector();
			Vector(std::initializer_list<T>);
			Vector(const size_t&);
			Vector(const Vector<T>&);
			Vector(Vector<T>&&);
			~Vector();

		public:
			Vector<T>&	operator= (const Vector<T>&);
			Vector<T>&	operator= (Vector<T>&&);

		public:
			bool	push_back(const T&);
			bool	pop_back();
			bool	push_front(const T&);
			bool	pop_front();
			bool	insert(const T&, const size_t&);
			void	resize(const size_t&);
			void	reserve(const size_t&);

		class	Iterator
		{
			public:
				Iterator(T*);
				~Iterator();

			public:
				T&			operator*();
				T*			operator->();
				Iterator&	operator++();
				Iterator	operator++(int);
				bool		operator==(const Iterator&) const;
				bool		operator!=(const Iterator&) const;

			public:
				Iterator	operator+(int n) const;
				Iterator	operator-(int n) const;
				bool		operator>(const Iterator& other) const;

			private:
				T*	_vec;
		};

		public:
			bool		pop(Iterator);
			Iterator	begin() const;
			Iterator	end() const;

		private:
			size_t	_size;
			size_t	_capacity;
			T*		_vector = nullptr;
	};

	template <typename T>
	Vector<T>::Vector() : _size(0), _capacity(0), _vector(nullptr) {}

  	template <typename T>
	Vector<T>::Vector(std::initializer_list<T> init_list) : _size(init_list.size()), _capacity(2*_size), _vector(new T[_capacity])
	{
		size_t index = 0;
        for (auto it = init_list.begin(); it != init_list.end(); ++it)
		{
            _vector[index] = *it;
			index++;
        }
	}

	template <typename T>
	Vector<T>::Vector(const size_t& size) : _size(size), _capacity(2*_size), _vector(new T[_capacity]) {}

	template <typename T>
	Vector<T>::Vector(const Vector<T>& vec) : _size(vec._size), _capacity(vec._capacity), _vector(new T[_capacity])
	{
		for(size_t i = 0; i < _size; ++i)
		{
			_vector[i] = vec._vector[i];
		}
	}

	template <typename T>
	Vector<T>::Vector(Vector<T>&& vec) : _size(vec._size), _capacity(vec._capacity), _vector(vec._vector)
	{
		vec._size = 0;
		vec._capacity = 0;
		vec._vector = nullptr;
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		delete[] _vector;
	}

	template <typename T>
	Vector<T>&	Vector<T>::operator= (const Vector<T>& vec)
	{
		if(this != &vec)
		{
			T* new_vector = new T[vec._capacity];
			for(size_t i = 0; i < vec._size; ++i)
			{
				new_vector[i] = vec._vector[i];
			}
			delete[] _vector;
			_vector = new_vector;
			_size = vec._size;
			_capacity = vec._capacity;
		}
		return (*this);
	}

	template <typename T>
	Vector<T>&	Vector<T>::operator= (Vector<T>&& vec)
	{
		if(this != &vec)
		{
			delete[] _vector;
			_vector = vec._vector;
			_size = vec._size;
			_capacity = vec._capacity;

			vec._size = 0;
			vec._capacity = 0;
			vec._vector = nullptr;
		}
		return (*this);
	}

	template<typename T>
	bool	Vector<T>::push_back(const T& newElement)
	{
		bool	status = false;
		if(_size == _capacity)
		{
			size_t newCapacity = _capacity == 0 ? 1 : 2 * _capacity;
			T*	tmp = new T[newCapacity];
			for(int i = 0; i < _size; ++i)
			{
				tmp[i] = _vector[i];
			}
			delete[] _vector;
			_vector = tmp;
			tmp = nullptr;
			_capacity = newCapacity;
		}
		_vector[_size++] = newElement;
		status = true;

		return (status);
	}

	template <typename T>
	bool	Vector<T>::pop_back()
	{
		if (_size == 0)
			return false;
		--_size;

		return true;
	}

	template <typename T>
	bool	Vector<T>::push_front(const T& newElement)
	{
		bool	status = false;
		if(_size >= _capacity)
		{
			size_t newCapacity = _capacity == 0 ? 1 : 2 * _capacity;
			T*	tmp = new T[newCapacity];
			tmp[0] = newElement;
			for(int i = 0; i < _size; ++i)
			{
				tmp[i + 1] = _vector[i];
			}
			delete[] _vector;
			_vector = tmp;
			tmp = nullptr;
			_capacity = newCapacity;
			_size++;
			status = true;
		}
		else
		{
			for (int i = (_size - 1); i >= 0; --i)
			{
				_vector[i + 1] = _vector[i];
			}
			_vector[0] = newElement;
			_size++;
			status = true;
		}
		return status;
	}

	template <typename T>
	bool	Vector<T>::pop_front()
	{
		bool	status = false;
		if(_size != 0)
		{
			for(int i = 0; i < _size; ++i)
			{
				_vector[i] = _vector[i + 1];
			}
			_size--;
			status = true;
		}
		return status;
	}

	template <typename T>
	bool	Vector<T>::insert(const T& newElement, const size_t& index)
	{
		bool	status = false;
		if(index <= _size)
		{
			if(index == _size)
				push_back(newElement);
			else if(index == 0)
				push_front(newElement);
			else
			{
				if(_size == _capacity)
				{
					size_t newCapacity = _capacity == 0 ? 1 : 2 * _capacity;
					T*	tmp = new T[newCapacity];
					for (size_t i = 0; i < index; i++)
					{
						tmp[i] = _vector[i];
					}
					tmp[index] = newElement;
					for(int i = index; i < _size; ++i)
					{
						tmp[i + 1] = _vector[i];
					}
					delete[] _vector;
					_vector = tmp;
					tmp = nullptr;
					_capacity = newCapacity;
					_size++;
					status = true;
				}
				else
				{
					for(int i = (_size - 1); i >= index; --i)
					{
						_vector[i + 1] = _vector[i];
					}
					_vector[index] = newElement;
					_size++;
					status = true;
				}
			}
		}
		return status;
	}

	template<typename T>
	void Vector<T>::resize(const size_t& newSize)
	{
		if (newSize < _size)
		{
			_size = newSize;
		}
		else if (newSize > _capacity)
		{
			reserve(newSize);
			_size = newSize;
		}
		else
		{
			_size = newSize;
		}
	}

	template<typename T>
	void Vector<T>::reserve(const size_t& newCapacity)
	{
		if (newCapacity > _capacity)
		{
			T* new_vector = new T[newCapacity];
			for (size_t i = 0; i < _size; ++i)
			{
				new_vector[i] = _vector[i];
			}
			delete[] _vector;
			_vector = new_vector;
			_capacity = newCapacity;
		}
	}

	template <typename T>
	bool	Vector<T>::pop(Vector<T>::Iterator itr)
	{
		if(itr > end())
			return false;
		if(itr == begin())
			pop_front();
		if(itr == end())
			pop_back();
		for(Vector<T>::Iterator it = itr; it != (end() - 1); ++it)
		{
			(*it) = *(it + 1);
		}
		_size--;
		return true;
	}

	template <typename T>
	Vector<T>::Iterator::Iterator(T* current) : _vec((current)) {}

	template <typename T>
	Vector<T>::Iterator::~Iterator() {}

	// T&	operator*();
	template <typename T>
	T&	Vector<T>::Iterator::operator* () {return *_vec;}

	// T*	operator->();
	template <typename T>
	T*	Vector<T>::Iterator::operator-> () {return _vec;}

	// Iterator<T>&	operator++();
	template <typename T>
	typename Vector<T>::Iterator&	Vector<T>::Iterator::operator++()
	{
		if(_vec)
			_vec++;
		return *this;
	}

	// Iterator<T>	operator++(int);
	template <typename T>
	typename Vector<T>::Iterator	Vector<T>::Iterator::operator++(int)
	{
		Iterator	temp = *this;
		++(*this);
		return temp;
	}

	// bool	operator==(const Iterator<T>&) const;
	template <typename T>
	bool	Vector<T>::Iterator::operator== (const Vector<T>::Iterator& other) const
	{
		return (this->_vec == other._vec);
	}

	// bool	operator!=(const Iterator<T>&) const;
	template <typename T>
	bool	Vector<T>::Iterator::operator!= (const Vector<T>::Iterator& other) const
	{
		return (this->_vec != other._vec);
	}


	template <typename T>
	typename Vector<T>::Iterator	Vector<T>::begin() const
	{
		if(_vector)
			return Iterator(_vector);
		else
			return Iterator(nullptr);
	}

	template <typename T>
	typename Vector<T>::Iterator	Vector<T>::end() const
	{
		if(_vector)
			return Iterator(&_vector[_size]);
		else
			return Iterator(nullptr);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator+(int n) const
	{
		Iterator temp = *this;
		temp._vec += n;
		return temp;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator-(int n) const
	{
		Iterator temp = *this;
		temp._vec -= n;
		return temp;
	}

	template <typename T>
	bool Vector<T>::Iterator::operator>(const Iterator& other) const
	{
		return _vec > other._vec;
	}

} // namespace my


#endif // __VECTOR_HPP__
