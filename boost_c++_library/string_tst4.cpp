#include <boost/algorithm/string.hpp> 
#include <string>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	std::string s = "\t Boris Sch?ling \t"; 
	std::cout << "." << boost::algorithm::trim_left_copy(s) << "." << std::endl; 
	std::cout << "." <<boost::algorithm::trim_right_copy(s) << "." << std::endl; 
	std::cout << "." <<boost::algorithm::trim_copy(s) << "." << std::endl; 

	return 0;
} 
