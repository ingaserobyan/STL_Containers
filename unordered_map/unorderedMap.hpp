#ifndef __UNORDERED_MAP_H__
#define __UNORDERED_MAP_H__

#include <iostream>
#include <vector>
#include <list>
#include <cmath>

template <typename K, typename V>
class UnorderedMap
{
	private:
		class Pair
		{
			public:
				Pair(const K& key, const V& val) : _key(key), _val(val) {}
				K	_key;
				V	_val;
		};

		using Bucket = std::list<Pair>;

	public:
		UnorderedMap(size_t bucket_count = 16);
		UnorderedMap(const K& key, const V& val, size_t bucket_count = 16);
		~UnorderedMap() = default;

		V&		operator[](const K& key);
		void	erase(const K& key);
		void	insert(const K& key, const V& val);
		void	print() const;

	private:
		size_t	custom_hash_function(const K& key) const;
		Bucket&	get_bucket(const K& key);
		void	resize_if_needed();

	private:
		std::vector<Bucket>	_buckets;
		size_t				_bucket_count;
		size_t				_size;
};

template <typename K, typename V>
UnorderedMap<K, V>::UnorderedMap(size_t bucket_count) : _bucket_count(bucket_count), _size(0), _buckets(bucket_count) {}

template <typename K, typename V>
UnorderedMap<K, V>::UnorderedMap(const K& key, const V& val, size_t bucket_count)
    : _bucket_count(bucket_count), _size(0), _buckets(bucket_count)
{
    insert(key, val);
}

template <typename K, typename V>
size_t	UnorderedMap<K, V>::custom_hash_function(const K& key) const
{
	size_t	hash_value = 0;
	std::string	key_string = std::to_string(key);

	for (char ch : key_string)
	{
		hash_value += ch;
	}

	return abs(hash_value) % _bucket_count;
}

template <typename K, typename V>
typename UnorderedMap<K, V>::Bucket&	UnorderedMap<K, V>::get_bucket(const K& key)
{
	return _buckets[custom_hash_function(key)];
}

template <typename K, typename V>
V& UnorderedMap<K, V>::operator[](const K& key)
{
	Bucket&	bucket = get_bucket(key);
	for (auto& pair : bucket)
	{
		if (pair._key == key)
			return pair._val;
	}

	bucket.push_back(Pair(key, V()));
	_size++;
	resize_if_needed();
	return bucket.back()._val;
}

template <typename K, typename V>
void UnorderedMap<K, V>::insert(const K& key, const V& val)
{
	Bucket&	bucket = get_bucket(key);
	for (auto& pair : bucket)
	{
		if (pair._key == key)
		{
			pair._val = val;
			return;
		}
	}

	bucket.push_back(Pair(key, val));
	_size++;
	resize_if_needed();
}

template <typename K, typename V>
void UnorderedMap<K, V>::erase(const K& key)
{
	Bucket&	bucket = get_bucket(key);
	bucket.remove_if([&key](const Pair& pair) { return pair._key == key; });
	_size--;
}

template <typename K, typename V>
void UnorderedMap<K, V>::print() const
{
	for (size_t i = 0; i < _bucket_count; ++i)
	{
		std::cout << "Bucket " << i << ": ";
		for (const auto& pair : _buckets[i])
		{
			std::cout << "[" << pair._key << ": " << pair._val << "] ";
		}
		std::cout << std::endl;
	}
}

template <typename K, typename V>
void UnorderedMap<K, V>::resize_if_needed()
{
	float	load_factor = static_cast<float>(_size) / static_cast<float>(_bucket_count);

	if (load_factor > 0.75)
	{
		size_t	new_bucket_count = _bucket_count * 2;
		std::vector<Bucket> new_buckets(new_bucket_count);

		for (const auto& bucket : _buckets)
		{
			for (const auto& pair : bucket)
			{
				size_t	new_index = abs(custom_hash_function(pair._key)) % new_bucket_count;
				new_buckets[new_index].push_back(pair);
			}
		}

		_buckets.swap(new_buckets);
		_bucket_count = new_bucket_count;
	}
}

#endif // __UNORDERED_MAP_H__
