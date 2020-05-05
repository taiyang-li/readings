#include <algorithm> 
#include <functional> 
#include <vector> 
#include <iostream> 
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

using namespace std;
class divide_by 
: public std::binary_function<int, int, int> 
{ 
	public: 
		int operator()(int n, int div) const 
		{ 
			return n / div; 
		} 
}; 

int divide_by1(int n, int div)
{
	return n/div;
}

int main() 
{ 
	std::vector<int> numbers; 
	numbers.push_back(10); 
	numbers.push_back(20); 
	numbers.push_back(30); 

	std::transform(numbers.begin(), numbers.end(), numbers.begin(), boost::bind(divide_by1, _1, 2));

	for_each(numbers.begin(), numbers.end(), cout << boost::lambda::_1 << "\n");	

	return 0;
} 
