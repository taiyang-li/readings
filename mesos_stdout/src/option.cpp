#include "stout/option.hpp"
#include <iostream>

int main()
{
  Option<int> a;
  std::cout << (a.isSome() ? "isSome" : "isNone") << std::endl;

  Option<int> b(100);
  std::cout << (b.isSome() ? "isSome" : "isNone") << std::endl;

  auto c = Option<int>::none();
  std::cout << (c.isSome() ? "isSome" : "isNone") << std::endl;

  auto d = Option<int>::some(10);
  std::cout << (d.isSome() ? "isSome" : "isNone") << std::endl;

  std::cout << ( a == c ? "a equals c" : "a not equal c") << std::endl;

  d = b;
  std::cout << ( b == d ? "b equals d" : "b not equal d") << std::endl;

  std::cout << a.get() << std::endl;
  std::cout << b.get() << std::endl;
  return 0;
}
