#include <boost/algorithm/string.hpp> 
#include <boost/algorithm/string/regex.hpp>
#include <boost/lambda/lambda.hpp>
#include <string>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	string a = "hello world";
	boost::iterator_range<string::iterator> r = boost::algorithm::find_regex(a, boost::regex("\\w\\s\\w"));
	cout << r << endl;
	return 0;
} 
