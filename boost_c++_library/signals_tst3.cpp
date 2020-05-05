#include <boost/signal.hpp> 
#include <iostream> 


void func1() 
{ 
	  std::cout << "Hello, " ; 
} 

void func2()
{
	std::cout << "world!" << std::endl;
}

int main() 
{ 
	  boost::signal<void ()> s; 
	  s.connect(1, func1); 
	  s.connect(0, func2); 
	  s.disconnect(func2);
	  s();
} 
