#include <iostream> 
#include <cstring> 
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp> 
#include <vector> 
#include <functional>
#include <algorithm>

using boost::shared_ptr;
using boost::ptr_vector;
using boost::bind;
using namespace std;

void add(int i, int j)
{
	cout << i+j << endl;
}

bool compare(int i, int j)
{
	return i<j;
}

void print(int i)
{
	cout << i << endl;
}

int main() 
{ 
	int a[4] = {4, 3, 2, 1};		
	vector<int> b(a, a+4);

	sort(b.begin(), b.end(), boost::bind(compare, _1, _2));
	for_each(b.begin(), b.end(), print);

	sort(b.begin(), b.end(), boost::bind(compare, _2, _1));
	for_each(b.begin(), b.end(), print);
	
	return 0;
} 
