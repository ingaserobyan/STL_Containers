#include <iostream>
#include <string>
#include "unorderedMap.hpp"

int main()
{
	UnorderedMap<int, std::string>	map(42, "The answer");

	// Insert more key-value pairs into the map
	map.insert(7, "Lucky number");
	map.insert(13, "Unlucky number");
	map.insert(100, "Century");
	map.insert(0, "Start");

	// Access and modify elements using the operator[]
	std::cout << "Value for key 42: " << map[42] << std::endl;
	std::cout << "Value for key 7: " << map[7] << std::endl;
	std::cout << "Value for key 100: " << map[100] << std::endl;

	// Modify value for an existing key
	map[42] = "Updated answer";
	std::cout << "Updated value for key 42: " << map[42] << std::endl;

	// Insert a new key-value pair using operator[]
	map[25] = "Quarter";
	std::cout << "Value for key 25: " << map[25] << std::endl;

	// Print the entire map
	std::cout << "\nContents of the map:" << std::endl;
	map.print();

	// Erase a key from the map
	map.erase(13);
	std::cout << "\nAfter erasing key 13:" << std::endl;
	map.print();

	// Check the map's response when accessing a non-existing key
	std::cout << "\nAccessing non-existing key 999:" << std::endl;
	std::cout << "Value for key 999: " << map[999] << std::endl;

	// Print the map after inserting a new element with operator[]
	std::cout << "\nAfter inserting key 999:" << std::endl;
	map.print();

	return 0;
}
