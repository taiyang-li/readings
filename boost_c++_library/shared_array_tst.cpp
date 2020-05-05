#include <iostream>
#include <boost/shared_array.hpp>
#include <vector>

using std::cout;
using std::endl;
using boost::shared_array;

int main()
{
	boost::shared_array<int> p(new int[2]);
	p[0] = 1;
	p[1] = 2;
	cout << "elem1: " << p[0] << ", elem2: " << p[1] << endl;
	return 0;
}
