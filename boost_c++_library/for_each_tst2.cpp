#include <iostream> 
#include <cstring> 
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/ptr_container/ptr_vector.hpp> 
#include <vector> 

using boost::shared_ptr;
using boost::ptr_vector;
using namespace std;

void print(int i)
{
	std::cout << i << std::endl;
}

class add : public binary_function<int, int, void>
{
	public:
	void operator()(int i, int j) const
	{
		cout << i+j << endl;
	}
};


int main() 
{ 
	int a[4] = {1, 2, 3, 4};		
	vector<int> b(a, a+4);
	for_each(b.begin(), b.end(), bind1st(add(), 10));
	return 0;
} 
