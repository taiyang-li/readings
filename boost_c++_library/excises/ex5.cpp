#include <vector> 
#include <iostream> 
#include <cstdlib> 
#include <cstring> 
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <algorithm>
#include <functional>

using namespace std;

typedef boost::function<int (const char*)>  processor;

void output(const processor& p, const char* data)
{
	cout << p(data) << endl;
}

int main() 
{
	vector<boost::function<int (const char*)> > processors;
	processors.push_back(std::atoi); 
	processors.push_back(std::strlen); 

	const char data[] = "1.23"; 

	/*
	for (std::vector<int(*)(const char*)>::iterator it = processors.begin(); it != processors.end(); ++it) 
		std::cout << (*it)(data) << std::endl; 
		*/

	for_each(processors.begin(), processors.end(), boost::bind(output, _1, data));
	return 0;
} 
