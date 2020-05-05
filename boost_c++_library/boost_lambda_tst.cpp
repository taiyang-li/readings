#include <iostream> 
#include <vector> 
#include <boost/lambda/lambda.hpp>

using namespace std;

int main() 
{ 
	int a[4] = {1,3,4,5};
	vector<int> b(a, a+4);
	for_each(b.begin(), b.end(), cout << boost::lambda::_1 + 10 << "\n");
	
	return 0;
} 
