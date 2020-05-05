#include <iostream>
#include <boost/shared_ptr.hpp>
#include <vector>

using std::cout;
using std::endl;
using boost::shared_ptr;

int main()
{
	std::vector<shared_ptr<int> > v;
	v.push_back(shared_ptr<int>(new int(1)));
	v.push_back(shared_ptr<int>(new int(2)));

	cout << "elem1: " << *v[0] << ", elem2: " << *v[1] << endl;
	return 0;
}
