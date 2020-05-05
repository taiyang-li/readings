#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <boost/thread.hpp>

using namespace std;

boost::mutex mutex;



using namespace std;

void init_number_generator()
{
	static boost::thread_specific_ptr<bool> tls;
	if (! tls.get())
	{
		tls.reset(new bool(false));
	}

	if (! *tls)
	{
		*tls = true;
		srand(static_cast<unsigned int>(time(0)));
	}
}
void random_number_generator()
{
	init_number_generator();
	int i = rand();
	boost::lock_guard<boost::mutex> lock(mutex);
	cout << i << endl;
}
int main() 
{ 
	boost::thread t[3];
	
	for (int i=0; i<3; i++)
	{
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		t[i] = boost::thread(random_number_generator);
	}

	for (int i=0; i<3; i++)
		t[i].join();

	return 0;
} 
