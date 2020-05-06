#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

int random_generator()
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

	// random generate a vector
	std::vector<int> a(7);
	std::vector<int> b(7);
	std::vector<int> c(7);
	std::generate(a.begin(), a.end(), random_generator);
	std::generate(b.begin(), b.end(), random_generator);
	std::generate(c.begin(), c.end(), random_generator);

	// sort
	std::sort(a.begin(), a.end());
	std::for_each(a.begin(), a.end(), print_element);
	std::cout << std::endl;

	// stable_sort 
	std::stable_sort(b.begin(), b.end());
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// partial sort 
	std::partial_sort(c.begin(), c.begin() + 5, c.end());
	std::for_each(c.begin(), c.end(), print_element);
	std::cout << std::endl;

	// partial sort copy	
	std::random_shuffle(c.begin(), c.end());
	std::partial_sort_copy(c.begin(), c.end(), a.begin(), a.begin()+5);
	std::for_each(a.begin(), a.end(), print_element);
	std::cout << std::endl;

	// nth_element
	std::vector<int> d(7);
	for(size_t i=0; i<7; i++)
	{
		d[i] = (i+1)*10;
	}
	std::random_shuffle(d.begin(), d.end());
	std::nth_element(d.begin(), d.begin()+2, d.end());
	std::for_each(d.begin(), d.end(), print_element);
	std::cout << std::endl;
	return 0;
}
