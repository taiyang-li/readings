#include "stout/uuid.hpp"
#include <iostream>
int main()
{
  UUID a = UUID::random();
  UUID b = UUID::fromBytes(a.toBytes());
  UUID c = UUID::fromString(a.toString());
  std::cout << a.toString()
    << "," << b.toString()
    << "," << c.toString() << std::endl;
  return 0;
}
