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

template <typename T>
class Min_Element
{
	public:
		typedef T result_type;

		template <typename InputIterator>
		T operator()(InputIterator first, InputIterator last)
		{
			return T(first, last);
		}
};

int main() 
{ 
	  boost::signal<int (), Min_Element<vector<int> > > s; 
	  s.connect(func1); 
	  s.connect(func2); 
	  vector<int> ret = s();
	  for_each(ret.begin(), ret.end(), cout << boost::lambda::_1 << "\n");
	  return 0;
} 
