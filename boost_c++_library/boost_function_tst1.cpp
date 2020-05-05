#include <iostream> 
#include <algorithm>
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace std;

class world 
{
public:
	void hello(ostream& os)
	{
		os << "hello, world" << endl;
	}
};

int main() 
{ 
	boost::function<void (world*, ostream&)> f = &world::hello;
	world w;
	f(&w, boost::ref(cout));
	return 0;
} 
