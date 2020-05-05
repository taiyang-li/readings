#include <boost/format.hpp>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	std::cout << boost::format("%|1$+| %2% %1%") %99 % 100 << std::endl; 
	return 0;
}
