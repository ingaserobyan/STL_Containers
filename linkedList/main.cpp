#include "node.hpp"
#include "singleList.hpp"


using IntIterator = typename my::singleList<int>::Iterator<int>;

void	print(my::singleList<int>&	head)
{
	for(IntIterator it = head.begin(); it!= head.end(); it++)
	{
		it->display();
	}
}

void	filterBelowAverage(my::singleList<int>&	head)
{
	int	average = head.average();

	for(IntIterator it = head.begin(); it != head.end(); ++it)
	{
		if(it->_data < average)
			head.pop(it);
	}
}

int main()
{
	my::Node<int> a(9);

	my::singleList<int> myList1(a);
	myList1.push_front(5);
	myList1.push_front(7);
	myList1.insert(4, 1);
	myList1.insert(a, 2);
	myList1.display();

	// std::cout << "Last: ";
	// my::Node<int>* b = myList1.findLastN(5);
	// b->display();

	myList1.reverse();
	myList1.display();

	if(myList1.isCyclic())
		std::cout << "List is cyclic" << std::endl;
	else
		std::cout << "List is NOT cyclic" << std::endl;

	print(myList1);

	filterBelowAverage(myList1);
	print(myList1);

	return 0;
}
