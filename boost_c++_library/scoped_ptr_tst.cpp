#include <iostream>
#include <boost/scoped_ptr.hpp>

using std::cout;
using std::endl;

int main()
{
	boost::scoped_ptr<int> p(new int);
	*p = 2;
	cout << *p << endl;
	*p.get() = 6;
	cout << *p << endl;
	p.reset(new int);
	cout << *p << endl;
	return 0;
}
