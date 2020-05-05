#include <iostream> 
#include <cstring> 
#include <boost/bind.hpp>
#include <vector> 
#include <functional>
#include <algorithm>

using namespace std;

void add(int i, int j, ostream& os)
{
	os << i+j << endl;
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

	for_each(b.begin(), b.end(), boost::bind(add, 10, _1, boost::ref(cout)));
	
	return 0;
} 
