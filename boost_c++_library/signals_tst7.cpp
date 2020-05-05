#include <boost/signal.hpp> 
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
			return *min_element(first, last);
		}
};

int main() 
{ 
	  boost::signal<int (), Min_Element<int> > s; 
	  s.connect(func1); 
	  s.connect(func2); 
	  cout << s() << endl;
	  return 0;
} 
