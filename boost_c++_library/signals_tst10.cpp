#include <boost/signal.hpp> 
#include <boost/lambda/lambda.hpp>
#include <iostream> 

using namespace std;

void func1() 
{ 
	cout << 1 << endl;
} 

void func2()
{
	cout << 2 << endl;
}

int main() 
{ 
	  boost::signal<void ()> s; 
	  boost::signals::connection c1= s.connect(func1); 
	  boost::signals::connection c2= s.connect(func2); 
	  s();
	  
	  c1.block();
	  s();
	  c2.block();
	  s();
	  return 0;
} 
