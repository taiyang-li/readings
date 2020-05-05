#include <boost/signal.hpp> 
#include <iostream> 

using namespace std;

void func1() 
{ 
	  std::cout << "Hello, "  << endl; 
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
	  cout << s.num_slots() << endl;
	  s.disconnect(func2);
	  cout << s.num_slots() << endl;
	  s();

	  s.disconnect_all_slots();
	  s();
	  cout << s.num_slots() << endl;
} 
