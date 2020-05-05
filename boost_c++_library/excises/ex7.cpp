#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <algorithm>
#include <sstream>

using namespace std;

bool get_hour_min(const string& input, int& hour, int& min)
{
	string tmp = input;
	replace(tmp.begin(), tmp.end(), ':', ' ');
	
	istringstream iss(tmp);
	iss >> hour >> min;
	return true;
}

int main()
{
	string input = "Munich Hamburg 92.12 8:25 9:45";
	// string output = "Munich    -> Hamburg      92.12 EUR (08:25-09:45)";
	
	boost::regex expr("(\\w+)\\s(\\w+)\\s([\\d\\.]+)\\s([\\d:]+)\\s([\\d:]+)");
	boost::smatch what;
	if (boost::regex_search(input, what, expr))
	{
		string src = what[1];
		string dst = what[2];
		string cost = what[3];
		string startTime = what[4];
		string endTime = what[5];
		int startHour, startMin;
		int endHour, endMin;

		get_hour_min(startTime, startHour, startMin);
		get_hour_min(endTime, endHour, endMin);
		cout << boost::format("%-10s\t->%-10s\t%+7s EUR (%02d:%02d-%02d:%02d)") %src %dst %cost %startHour %startMin %endHour %endMin << endl;
	}

	return 0;
}
