#include <iostream>
#include "vector.hpp"
#include <vector>
#include <iterator>
#include <algorithm>

void printVec(my::Vector<int> v)
{
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
}

bool	is_prime(int n)
{
	if(n <= 1)
		return false;
	for(int i = 2; (i * i) <= n; ++i)
	{
		if(n % i == 0)
			return false;
	}
	return true;
}

void	filterNotPrimes(my::Vector<int>& v)
{
	for(my::Vector<int>::Iterator itr = v.begin(); itr != v.end(); ++itr)
	{
		if(is_prime(*itr))
		{
			v.pop(itr);
			itr = itr - 1;
		}
	}
}

int main()
{
    my::Vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

	// for(int i = 1; i <= 10; ++i)
	// 	v.push_back(i);

    std::cout << "Vector: ";
	printVec(v);

	// v.reserve(20);
    // std::cout << "After reserve(20): ";
    // printVec(v);

	// v.resize(8);
    // std::cout << "After resize(8): ";
    // printVec(v);

    // v.pop_back();
    // std::cout << "After pop_back: ";
    // printVec(v);

    // v.insert(4, 1);
    // std::cout << "Vector after insert: ";
    // printVec(v);

	filterNotPrimes(v);
	std::cout << "After PRIME filter: ";
	printVec(v);

	std::vector<int> vec = {2, 3, 10, 80, 21, 4, 0};
	std::sort(vec.begin(), vec.end());

	for(auto it : vec)
		std::cout << it << " " ;
	std::cout << std::endl;

    return 0;
}
