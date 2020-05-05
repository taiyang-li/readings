#include <boost/signal.hpp> 
#include <boost/lambda/lambda.hpp>
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
	  boost::signals::connection c1= s.connect(func1); 
	  boost::signals::connection c2= s.connect(func2); 
	  cout << s() << endl;
	  c1.disconnect();
	  c2.disconnect();
	  return 0;
} 
