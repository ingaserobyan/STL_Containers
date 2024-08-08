#include "map.hpp"
#include <string>

int main()
{
	Map<int, std::string>	my_map(4, "Sam");

	my_map.insert(5, "Paul");
	my_map.insert(2, "John");
	my_map.insert(7, "Don");
	my_map.insert(1, "Me");
	my_map.insert(0, "You");
	my_map.insert(33, "Ittt");
	my_map.insert(8, "oooo");
	my_map.insert(9, "aaaa");
	my_map.insert(36, "bbbbb");

	my_map.PrintInorderRecursive();

	std::cout << std::endl;
	std::cout << "operator[] = " << my_map[4] << std::endl;
	std::cout << std::endl;

	std::cout << "Erasingggg" << std::endl;
	my_map.erase(0);
	my_map.PrintInorderRecursive();

	// std::cout << "___for copy ctor___" << std::endl;
	// Map<int, std::string> copy_map = my_map;
	// copy_map.inorderRecursive();
	return 0;
}

// int main()
// {
// 	Map<char, int> experiment;
// 	experiment.insert('a', 12);
// 	experiment.insert('g', 16);
// 	experiment.insert('b', 30);
// 	experiment.insert('[', 100);

// 	std::cout << "operator[] = " << experiment['g'] << std::endl;

// 	experiment.inorderRecursive();
// }
