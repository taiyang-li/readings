#include <iostream> 
#include <cstring> 
#include <vector> 
#include <functional>
#include <algorithm>
#include <boost/function.hpp>

using namespace std;

int main() 
{ 
	try
	{
		boost::function<int (const char*)> f;
		cout << f("isqghdf") << endl;
	}
	catch(boost::bad_function_call& e)
	{
		cout << e.what() << endl;
	}
	return 0;
} 
