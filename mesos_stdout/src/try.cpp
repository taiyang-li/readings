#include "stout/try.hpp"

int main()
{
  auto a = Try<int>::some(100);
  auto b = Try<int>::error("hello");
  
  std::cout << (a.isSome() ? "a is some" : "a is error") << std::endl;
  std::cout << (b.isSome() ? "b is some" : "b is error") << std::endl;
  
  std::cout << " b: " << b.error() << std::endl;
  // std::cout << " b: " << b.get() << std::endl;
  b = a;
  std::cout << " b: " << b.get() << std::endl;
  return 0;
}
