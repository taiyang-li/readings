#include <boost/regex.hpp>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s = "hello world";
	boost::regex expr("\\s");
	string fmt("_");
	boost::regex_replace(s, expr, fmt);
	cout << s << endl;
	return 0;
}
