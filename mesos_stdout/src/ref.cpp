#include <functional>
#include <iostream>
int main()
{
  int foo = 10;
  auto bar = std::ref(foo);
  bar++;
  std::cout << foo << std::endl;
  auto bar1 = std::cref(foo);
  foo++;
  std::cout << bar1 << std::endl;
  return 0;
}
