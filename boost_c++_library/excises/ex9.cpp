#include <boost/date_time/posix_time/posix_time.hpp> 
#include <boost/cstdint.hpp> 
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream> 

using namespace std;

void add(int begin, int end, boost::uint64_t& sum)
{
	sum = 0;
	for (int i=begin; i<end; i++)
	{
		sum += i;
	}
}

int main() 
{ 
	// 获取服务器thread 数目 
	const int threadNo(boost::thread::hardware_concurrency());

	boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time(); 

	boost::uint64_t part[threadNo];
	boost::uint64_t sum = 0; 

	boost::thread t[threadNo];
	
	for (int i=0; i<threadNo; i++)
	{
		t[i] = boost::thread(add, i*(1000000000/threadNo), (i+1)*(1000000000/threadNo), boost::ref(part[i]));
	}

	for (int i=0; i<threadNo; i++)
	{
		t[i].join();
		cout << part[i] << endl;
	}
	
	for (int i=0; i<threadNo; i++)
	{
		sum += part[i];
	}
	
	boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time(); 
	std::cout << end - start << std::endl; 
	cout << sum << endl;

	return 0;

} 
