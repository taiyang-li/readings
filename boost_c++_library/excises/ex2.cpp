#include <iostream> 
#include <cstring> 
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/ptr_container/ptr_vector.hpp> 
#include <vector> 

using boost::shared_ptr;
using boost::ptr_vector;

template <typename T> 
T* create() 
{ 
	return new T;
} 

int main() 
{ 
	ptr_vector<int> v;
	v.push_back(create<int>()); 
	return 0;
} 
