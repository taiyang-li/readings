#include <boost/functional/hash.hpp>
#include <iostream>

struct Point
{
  int x;
  int y;
};

int main()
{
  size_t seed = 0;
  Point p = {3, 4};
  boost::hash_combine(seed, p.x);
  boost::hash_combine(seed, p.y);
  std::cout << seed << std::endl;

  std::vector<std::string> a = {"hello", "world"};
  std::cout << boost::hash_range(begin(a), end(a)) << std::endl;
  return 0;
}
