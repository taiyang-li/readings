#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <boost/thread.hpp>

using namespace std;

boost::mutex mutex;

void wait(int seconds)
{
	boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

void thread()
{
	for(int i=0; i<5; i++)
	{
		wait(1);
		mutex.lock();		
		cout << "id: " << boost::this_thread::get_id() << endl;
		cout << i << endl;
		mutex.unlock();
	}
}

using namespace std;

int main() 
{ 
	boost::thread t1(thread);
	boost::thread t2(thread);
	t1.join();
	t2.join();
	return 0;
} 
