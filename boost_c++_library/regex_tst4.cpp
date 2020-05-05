#include <boost/regex.hpp>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s = "hello world";
	boost::regex expr("(\\w+)\\s(\\w+)");
	string fmt("\\2 \\1");
	cout << boost::regex_replace(s, expr, fmt, boost::regex_constants::format_literal) << endl;
	return 0;
}
