#include <algorithm>
#include <iostream>
#include <vector>

bool is_gt_50(int n)
{
	return n>50;
}

inline void print_element(int n)
{
	std::cout << n << std::endl;
}

int main()
{
	srand((unsigned int)time(0));
	std::vector<int> a(10);
	for(std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		*it = rand() % 100;

	// partition
	std::vector<int>::iterator it = std::partition(a.begin(), a.end(), is_gt_50);	
	std::for_each(a.begin(), it, print_element);
	std::cout << std::endl;
	std::for_each(it, a.end(), print_element);
	std::cout << std::endl;

	// stable_partition
	std::random_shuffle(a.begin(), a.end());
	it = std::stable_partition(a.begin(), a.end(), is_gt_50);
	std::for_each(a.begin(), it, print_element);
	std::cout << std::endl;
	std::for_each(it, a.end(), print_element);
	std::cout << std::endl;
	return -1;
}

