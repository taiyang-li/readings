#include <iostream>
#include <boost/lexical_cast.hpp>

bool equal(int64_t a, uint64_t b)
{
  if (a < 0)
    return false;
  return boost::lexical_cast<uint64_t>(a) == b;
}

int main()
{
  if (equal(-1, -1))
    std::cout << "-1 equal -1" << std::endl;
  if (equal(10, 10))
    std::cout << "10 equal 10" << std::endl;
  return 0;
}
