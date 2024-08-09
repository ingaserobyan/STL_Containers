#ifndef __UNORDERED_MAP_H__
#define __UNORDERED_MAP_H__

#include <iostream>
#include <vector>
#include <list>
#include <functional>

template <typename K, typename V>
class UnorderedMap
{
private:
    class Pair
    {
    public:
        Pair(const K& key, const V& val);
        ~Pair() = default;

    public:
        K _key;
        V _val;
    };

public:
    UnorderedMap(size_t bucket_count = 16);
    ~UnorderedMap();

    V& operator[](const K& key);
    void erase(const K& key);
    void insert(const K& key, const V& val);
    void print() const;

private:
    size_t get_bucket_index(const K& key) const;
    Pair* find_in_bucket(const K& key, size_t bucket_index);

private:
    std::vector<std::list<Pair>> _buckets;
    std::hash<K> _hasher;
};

// UnorderedMap::Pair
template <typename K, typename V>
UnorderedMap<K, V>::Pair::Pair(const K& key, const V& val) : _key(key), _val(val) {}

// UnorderedMap methods
template <typename K, typename V>
UnorderedMap<K, V>::UnorderedMap(size_t bucket_count)
{
    _buckets.resize(bucket_count);
}

template <typename K, typename V>
UnorderedMap<K, V>::~UnorderedMap() {}

template <typename K, typename V>
size_t UnorderedMap<K, V>::get_bucket_index(const K& key) const
{
    return _hasher(key) % _buckets.size();
}

template <typename K, typename V>
typename UnorderedMap<K, V>::Pair* UnorderedMap<K, V>::find_in_bucket(const K& key, size_t bucket_index)
{
    for (auto& pair : _buckets[bucket_index])
    {
        if (pair._key == key)
            return &pair;
    }
    return nullptr;
}

template <typename K, typename V>
V& UnorderedMap<K, V>::operator[](const K& key)
{
    size_t bucket_index = get_bucket_index(key);
    Pair* pair = find_in_bucket(key, bucket_index);

    if (pair)
    {
        return pair->_val;
    }
    else
    {
        _buckets[bucket_index].emplace_back(key, V());
        return _buckets[bucket_index].back()._val;
    }
}

template <typename K, typename V>
void UnorderedMap<K, V>::insert(const K& key, const V& val)
{
    size_t bucket_index = get_bucket_index(key);
    Pair* pair = find_in_bucket(key, bucket_index);

    if (pair)
    {
        pair->_val = val;
    }
    else
    {
        _buckets[bucket_index].emplace_back(key, val);
    }
}

template <typename K, typename V>
void UnorderedMap<K, V>::erase(const K& key)
{
    size_t bucket_index = get_bucket_index(key);
    auto& bucket = _buckets[bucket_index];

    for (auto it = bucket.begin(); it != bucket.end(); ++it)
    {
        if (it->_key == key)
        {
            bucket.erase(it);
            return;
        }
    }
}

template <typename K, typename V>
void UnorderedMap<K, V>::print() const
{
    for (size_t i = 0; i < _buckets.size(); ++i)
    {
        std::cout << "Bucket " << i << ": ";
        for (const auto& pair : _buckets[i])
        {
            std::cout << "[" << pair._key << ": " << pair._val << "] ";
        }
        std::cout << std::endl;
    }
}

#endif // __UNORDERED_MAP_H__
