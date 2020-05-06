#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

inline void print_element(int n)
{
	std::cout << n << std::endl;
}

inline int inc_element(int n)
{
	return n+11; 
}

inline bool is_gt_10(int n)
{
	return n > 10;
}

inline bool is_eq_10(int n)
{
	return n==10;
}

inline int random_generator()
{
	return rand() % 3;
}

inline int is_even(int n)
{
	return n % 2 == 0;
}

int main()
{	
	// copy 
	int a[7] = {1,2,3,4,5,6,7};
	std::vector<int> b(7);
	std::copy(a, a+7, b.begin());
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// copybackward
	std::copy_backward(a, a+5 , b.end());
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// swap
	int c = 10;
	int d = 20;
	std::swap(c, d);
	print_element(c);
	print_element(d);
	std::cout << std::endl;

	// swap_range 
	std::reverse(b.begin(), b.end());
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	std::swap_ranges(a, a+7, b.begin());
	std::for_each(a, a+7, print_element);
	std::cout << std::endl;
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// iter_range
	std::iter_swap(a, b.begin());
	std::cout << *a << " " << *(b.begin()) << std::endl;

	// transform 
	std::transform(a, a+7 ,a, inc_element);
	std::for_each(a, a+7, print_element);
	std::cout << std::endl;

	// replace 
	std::replace(a, a+7, 12, 10);
	std::for_each(a, a+7, print_element);
	std::cout << std::endl;

	// replace_if 
	std::replace_if(a, a+7, is_gt_10, 1);
	std::for_each(a, a+7, print_element);
	std::cout << std::endl;
	
	// replace_copy
	std::replace_copy(a, a+7, b.begin(), 10, 1);
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// replace_copy_if 
	std::replace_copy_if(a, a+7, b.begin(), is_eq_10, 1);
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// fill 
	std::fill(b.begin(), b.end(), 100);
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// fill_n 
	std::fill_n(b.begin(), 2, 10);
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// generate 
	srand((unsigned int)time(0));
	std::generate(b.begin(), b.end(), random_generator);
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// generator_n
	std::generate_n(b.begin(), 2, random_generator);
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// remove 
	std::vector<int>::iterator it = std::remove(b.begin(), b.end(), 1);
	std::for_each(b.begin(), it, print_element);
	std::cout << std::endl;

	// remove_if 
	it = std::remove_if(b.begin(), b.end(), is_even);
	std::for_each(b.begin(), it, print_element);
	std::cout << std::endl;

	// remove_copy 
	std::generate_n(b.begin(), 2, random_generator);
	int* p = std::remove_copy(b.begin(), b.end(), a, 23);
	std::for_each(a, p, print_element);
	std::cout << std::endl;

	// remove_copu_if 
	p = std::remove_copy_if(b.begin(), b.end(), a, is_even);
	std::for_each(a, p, print_element);
	std::cout << std::endl;

	// unique 
	std::generate(b.begin(), b.end(), random_generator);
	it = std::unique(b.begin(), b.end());
	std::for_each(b.begin(), it, print_element);
	std::cout << std::endl;

	// unique 
	std::generate(b.begin(), b.end(), random_generator);
	p = std::unique_copy(b.begin(), b.end(), a);
	std::for_each(a, p, print_element);
	std::cout << std::endl;

	// reverse 
	std::reverse(b.begin(), b.end());
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// reverse_copy 
	std::reverse_copy(b.begin(), b.end(), a);
	std::for_each(a, a+7, print_element);
	std::cout << std::endl;

	// rotate 
	std::rotate(a, a+3, a+7);
	std::for_each(a, a+7, print_element);
	std::cout << std::endl;

	// rotate_copy 
	std::rotate_copy(a, a+4, a+7, b.begin());
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;

	// random_shuffle
	std::random_shuffle(b.begin(), b.end());
	std::for_each(b.begin(), b.end(), print_element);
	std::cout << std::endl;
	return 0;
}
