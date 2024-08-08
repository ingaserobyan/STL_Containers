#ifndef __MAP_H__
#define __MAP_H__

//K is key type
//V is value type

#include <iostream>

template <typename K, typename V>
class Map
{
	private:
		class	Pair
		{
			public:
				Pair(const K& key, const V& val);
				~Pair() = default;

			public:
				K	_key;
				V	_val;
		};

	private:
		class	BT_Node
		{
			public:
				BT_Node(const BT_Node& node_copy_from);
				BT_Node(const K& key, const V& val);
				~BT_Node();

			public:
				Pair	*_element;
				BT_Node	*_left;
				BT_Node	*_right;
		};

	public:
		Map();
		Map(const K& key, const V& val);
		Map(const Map<K, V>&);

	public:
		~Map();

	public:
		Map&		operator=(const Map<K, V>&);
		V&			operator[](const K&);
		void		erase(const K& key);
		void		insert(const K& key, const V& val);
		void		PrintInorderRecursive() const;

	private:
		BT_Node*	insert_helper(BT_Node* current_root, const K& key, const V& val);
		BT_Node*	erase_helper(BT_Node* current_root, const K& key);
		BT_Node*	find_min(BT_Node* node) const;
		BT_Node*	find_max(BT_Node* node) const;
		void		PrintInorderRecursiveHelper(BT_Node *current_root) const;

	private:
		BT_Node*	_root = nullptr;
};


//Map::Pair
template <typename K, typename V>
Map<K,V>::Pair::Pair(const K& key, const V& val) : _key(key), _val(val) {};

//Map::BT_Node
template <typename K, typename V>
Map<K, V>::BT_Node::BT_Node(const BT_Node& node_copy_from) :
	_element(new Pair(node_copy_from._element->_key, node_copy_from._element->_val)),
	_left(nullptr),
	_right(nullptr)
{
	if (node_copy_from._left != nullptr)
		_left = new BT_Node(*node_copy_from._left);
	if (node_copy_from._right != nullptr)
		_right = new BT_Node(*node_copy_from._right);
}

template <typename K, typename V>
Map<K, V>::BT_Node::BT_Node(const K& key, const V& val) :
	_element(new Pair(key, val)), _left(nullptr), _right(nullptr) {}

template <typename K, typename V>
Map<K, V>::BT_Node::~BT_Node()
{
	if (_left != nullptr)
		delete	_left;
	if (_right != nullptr)
		delete	_right;
	if (_element != nullptr)
		delete _element;
}

//Map (ctors and dtor)
template <typename K, typename V>
Map<K, V>::Map() {_root = nullptr;}

template <typename K, typename V>
Map<K, V>::Map(const K& key, const V& val) {_root = new BT_Node(key, val);}

template <typename K, typename V>
Map<K, V>::Map(const Map<K, V>& copy_from) : _root(nullptr)
{
	std::cout << "copy ctor called" << std::endl;
	if (copy_from._root)
		 _root = new Map::BT_Node(*(copy_from._root));
}

template <typename K, typename V>
Map<K, V>::~Map() {delete _root;}


//Map_methods

//operator=
template<typename K, typename V>
Map<K,V>&	Map<K,V>::operator=(const Map<K, V>& other)
{
	if (this != &other)
	{
		delete _root;
		_root = nullptr;
		if (other._root != nullptr)
			_root = new BT_Node(*(other._root));
	}
	return *this;
}

//operator[]
template<typename K, typename V>
V&	Map<K, V>::operator[] (const K& key)
{
	BT_Node* tmp = _root;
	BT_Node* parent = nullptr;

	while (tmp != nullptr)
	{
		if (key == tmp->_element->_key)
			return tmp->_element->_val;
		parent = tmp;
		if (key < tmp->_element->_key)
			tmp = tmp->_left;
		else
			tmp = tmp->_right;
	}

    BT_Node* newNode = new BT_Node(key, V());

    if (parent == nullptr)
        _root = newNode;
    else if (key < parent->_element->_key)
        parent->_left = newNode;
    else
        parent->_right = newNode;

    return newNode->_element->_val;
}

//erase
template <typename K, typename V>
void	Map<K, V>::erase(const K& key)
{
	_root = erase_helper(_root, key);
}

template <typename K, typename V>
typename Map<K, V>::BT_Node*	Map<K, V>::erase_helper(BT_Node* current_root, const K& key)
{
	if (current_root == nullptr)
		return current_root;

	if (key < current_root->_element->_key)
		current_root->_left = erase_helper(current_root->_left, key);
	else if (key > current_root->_element->_key)
		current_root->_right = erase_helper(current_root->_right, key);
	else
	{
		if (current_root->_left == nullptr && current_root->_right == nullptr)
		{
			delete current_root;
			return nullptr;
		}

		if (current_root->_right != nullptr)
		{
			BT_Node*	temp = find_min(current_root->_right);
			current_root->_element->_key = temp->_element->_key;
			current_root->_element->_val = temp->_element->_val;
			current_root->_right = erase_helper(current_root->_right, temp->_element->_key);
		}
		else
		{
			BT_Node*	temp = find_max(current_root->_left);
			current_root->_element->_key = temp->_element->_key;
			current_root->_element->_val = temp->_element->_val;
			current_root->_left = erase_helper(current_root->_left, temp->_element->_key);
		}
	}
	return current_root;
}

template <typename K, typename V>
typename Map<K, V>::BT_Node*	Map<K, V>::find_min(BT_Node* node) const
{
	BT_Node*	current = node;
	while (current && current->_left != nullptr)
		current = current->_left;
	return current;
}

template <typename K, typename V>
typename Map<K, V>::BT_Node*	Map<K, V>::find_max(BT_Node* node) const
{
	BT_Node*	current = node;
	while (current && current->_right != nullptr)
		current = current->_right;
	return current;
}

//insert
template <typename K, typename V>
void	Map<K, V>::insert(const K& key, const V& val)
{
	_root = insert_helper(_root, key, val);
}

template <typename K, typename V>
typename Map<K,V>::BT_Node*	Map<K,V>::insert_helper(BT_Node* current_root, const K& key, const V& val)
{
	if (current_root == nullptr)
		return new BT_Node(key, val);
	if (key < current_root->_element->_key)
		current_root->_left = insert_helper(current_root->_left, key, val);
	else if (key > current_root->_element->_key)
		current_root->_right = insert_helper(current_root->_right, key, val);
	else
		current_root->_element->_val = val;
	return current_root;
}

//printing
template <typename K, typename V>
void	Map<K, V>::PrintInorderRecursiveHelper(BT_Node *current_node) const
{
	if (current_node == nullptr)
		return;
	PrintInorderRecursiveHelper(current_node->_left);
	std::cout << current_node->_element->_key << " : " << current_node->_element->_val << " " << std::endl;
	PrintInorderRecursiveHelper(current_node->_right);
}

template <typename K, typename V>
void	Map<K, V>::PrintInorderRecursive() const
{
	PrintInorderRecursiveHelper(_root);
}
#endif // __MAP_H__
