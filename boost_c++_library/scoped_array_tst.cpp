#include <boost/scoped_array.hpp>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	boost::scoped_array<int> i(new int[2]);
	*i.get() = 1;
	i[1] = 2;
	cout << "elem1: " << i[0] << ", elem2: " << i[1] << endl;
	i.reset(new int[3]);
	return 0;
}
