#include <algorithm>
#include <iostream>

int main()
{	
	int a[10] = {1,1,2,3,5,6,6,7,7,8};

	// lower_bound
	int *p1 = std::lower_bound(a, a+10, 5);
	std::cout << "lower bound " << p1 - a << std::endl;

	// upper_bound
	int *p2 = std::upper_bound(a, a+10, 5);
	std::cout << "lower bound " << p2 - a << std::endl;

	// equal_range
	std::pair<int*, int*> pr = std::equal_range(a, a+10, 5);
	for(int* tmp = pr.first; tmp != pr.second; tmp++)
	{
		std::cout << *tmp << std::endl;
	}

	// binary_seatch
	if (std::binary_search(a,a+10, 4))
		std::cout << "can't find 4 in a" << std::endl;
	else
		std::cout << "find 4 in a" << std::endl;

	return 0;
}
