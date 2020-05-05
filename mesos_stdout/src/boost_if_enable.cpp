#include <boost/utility/enable_if.hpp>
#include <iostream>

template <typename T>
void print(typename boost::enable_if<std::is_integral<T>, T>::type i)
{
  std::cout << "Intergral: " << i << std::endl; 
}

template <typename T>
void print(typename boost::enable_if<std::is_floating_point<T>, T>::type f)
{
  std::cout << "Floating: " << f << std::endl;
}

int main()
{
  print<int>(10);
  print<float>(1.1);
  return 0;
}
  
