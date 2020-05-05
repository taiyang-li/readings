#include <boost/algorithm/string.hpp> 
#include <boost/lambda/lambda.hpp>
#include <string>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	string a = "hello world";
	vector<string> v;
	boost::algorithm::split(v, a, boost::algorithm::is_space());
	for_each(v.begin(), v.end(), cout << boost::lambda::_1 << "\n");
	return 0;
} 
