#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

int main()
{
	string s = "<person><name>Karl-Heinz Huber</name><dob>1970-9-30</dob><account>2,900.64 USD</account></person>";		
	
	string name;
	string birthday;
	string balance;

	boost::smatch what;
	boost::regex expr("<name>(.*)</name><dob>(.*)</dob><account>(.*)</account>");
	if (boost::regex_search(s, what, expr))
	{
		name = what[1];
		birthday = what[2];
		balance = what[3];
		cout << name << ", " << birthday << ", " << balance << endl;
	}
	


	return 0;
}
