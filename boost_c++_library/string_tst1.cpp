#include <boost/algorithm/string.hpp> 
#include <locale> 
#include <iostream> 

int main() 
{ 
	std::string s = "Boris Sch?ling"; 
	boost::iterator_range<std::string::iterator> r = boost::algorithm::find_first(s, "Boris"); 
	std::cout << r << std::endl; 
	r = boost::algorithm::find_first(s, "xyz"); 
	std::cout << r << std::endl; 
} 
