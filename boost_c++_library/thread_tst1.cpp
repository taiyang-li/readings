#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <boost/thread.hpp>

using namespace std;

void wait(int seconds) 
{ 
	boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

void thread() 
{ 
	for (int i = 0; i < 5; ++i) 
	{ 
		wait(1); 
		std::cout << i << std::endl; 
	} 
} 

int main() 
{ 
	boost::thread t(thread); 
	t.join(); 
} 
