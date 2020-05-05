#include <boost/algorithm/string.hpp> 
#include <string>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	vector<string> a;	
	a.push_back("hello");
	a.push_back("world");
	cout << boost::algorithm::join(a, " ") << endl;
	
	return 0;
} 
