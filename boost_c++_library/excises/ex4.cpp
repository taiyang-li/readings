#include <string> 
#include <vector> 
#include <iostream> 
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

using namespace std;

void insert_size(vector<int>& sizes, const string& s)
{
	sizes.push_back(s.size());
}

int main() 
{ 
	std::vector<std::string> strings; 
	strings.push_back("Boost"); 
	strings.push_back("C++"); 
	strings.push_back("Libraries"); 

	std::vector<int> sizes; 

	/*
	for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it) 
		sizes.push_back(it->size()); 
		*/

	/*
	for (std::vector<int>::iterator it = sizes.begin(); it != sizes.end(); ++it) 
		std::cout << *it << std::endl; 
		*/

	for_each(strings.begin(), strings.end(), boost::bind(insert_size, boost::ref(sizes), _1));

	for_each(strings.begin(), strings.end(), cout << boost::lambda::_1 << "\n");

	return 0;
} 
