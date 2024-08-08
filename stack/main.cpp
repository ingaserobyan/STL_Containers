#include "stackVector.hpp"
#include "stackList.hpp"
#include <iostream>

int main()
{

	//      With V E C T O R
	std::cout << std::endl;
	std::cout << "__With Vector__" << std::endl;
	std::cout << std::endl;
	Stack_Vec<int> stck;
	stck.push(5);
	std::cout << "pushed to stck: " << stck.back() << std::endl;
	stck.push(4);
	std::cout << "pushed to stck: " << stck.back() << std::endl;
	stck.push(3);
	std::cout << "pushed to stck: " << stck.back() << std::endl;

	Stack_Vec<int> tmp = stck;

	stck.pop();
	std::cout << "poped from stck" << std::endl;
	std::cout << "stck back() -> " << stck.back() << std::endl;

	std::cout << "tmp back() -> " << tmp.back() << std::endl;


	//      With L I S T
	std::cout << std::endl;
	std::cout << "__With List__" << std::endl;
	std::cout << std::endl;
	Stack_lst<int> s1;
	s1.push(5);
	s1.push(7);
	s1.push(2);
	std::cout << s1.back() << std::endl;
}