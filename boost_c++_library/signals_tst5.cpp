#include <boost/signal.hpp> 
#include <iostream> 

using namespace std;

int func1() 
{ 
	return 1;
} 

int func2()
{
	return 2;
}

int main() 
{ 
	  boost::signal<int ()> s; 
	  s.connect(func1); 
	  s.connect(func2); 
	  cout << s() << endl;
	  return 0;
} 
