#include <boost/format.hpp>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << boost::format("%1%.%2%.%3%") %1 %2 %3 << endl;
	return 0;
}
