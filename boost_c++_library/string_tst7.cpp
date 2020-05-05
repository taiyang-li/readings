#include <boost/algorithm/string.hpp> 
#include <string>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	string s = "123456789algorithm128638634";
	cout << boost::algorithm::starts_with(s, "123") << endl;
	cout << boost::algorithm::ends_with(s, "634") << endl;
	cout << boost::algorithm::ends_with(s, "algorithm") << endl;
	cout << boost::algorithm::lexicographical_compare(s, "Boris") << std::endl; 
	return 0;
} 
