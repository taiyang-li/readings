#include <iostream>
#include <boost/tuple/tuple.hpp>

int main()
{
  typedef boost::tuple<int, char, std::string> person;
  person p(100, 'A', "hello");
  std::cout << p.get<0>() << std::endl;
  std::cout << p.get<1>() << std::endl;
  std::cout << p.get<2>() << std::endl;

  person p1 = boost::make_tuple<int, char, std::string>(101, 'B', "world");
  return 0;
}
