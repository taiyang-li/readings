#include <algorithm>
#include <iostream>
#include <vector>

inline int random_generator()
{
	return rand() % 100;
}

inline void print_element(int n)
{	
	std::cout << n << std::endl;
}


int main()
{
	srand((unsigned int)time(0));
	std::vector<int> a(7);
	std::generate(a.begin(), a.end(), random_generator);

	std::make_heap(a.begin(), a.end());
	std::cout << "after make_heap: " << std::endl;
	std::for_each(a.begin(), a.end(), print_element);

	a.push_back(55);
	std::push_heap(a.begin(), a.end());
	std::cout << "after push_heap 55: " << std::endl;
	std::for_each(a.begin(), a.end(), print_element);

	std::pop_heap(a.begin(), a.end());
	a.pop_back();
	std::cout << "after pop_heap" << std::endl;
	std::for_each(a.begin(), a.end(), print_element);

	std::sort_heap(a.begin(), a.end());
	std::cout << "after sort_heap" << std::endl;
	std::for_each(a.begin(), a.end(), print_element);
	return 0;
}

