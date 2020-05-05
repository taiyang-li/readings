#include <string>
#include <boost/regex.hpp>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	string s = "hello world";
	boost::regex expr("(\\w+)\\s(\\w+)");
	boost::smatch what;
	if (boost::regex_search(s, what, expr))
	{
		cout << "first: " << what[0] << endl;
		cout << "second: " << what[1] << endl;
		cout << "third: " << what[2] << endl;
	}

	return 0;
} 
