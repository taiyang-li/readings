#include <iostream> 
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

int sum1 = 0; 
int sum2 = 0;

void getSum(int begin, int end, int& ret)
{
	ret = 0;
	for (int i=begin; i<end; i++)
		ret += i;
}

void calculate() 
{
	boost::thread t[2];
	t[0] = boost::thread(getSum, 0, 50, boost::ref(sum1));
	t[1] = boost::thread(getSum, 50, 100, boost::ref(sum2));
	t[0].join();
	t[1].join();
} 

void print() 
{ 
	std::cout << sum1 << std::endl; 
	std::cout << sum1+ sum2 << std::endl;
} 

void thread() 
{ 
	calculate(); 
	print(); 
} 

int main() 
{ 
	thread(); 
} 
