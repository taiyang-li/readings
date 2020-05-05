#include "stout/result.hpp"
#include "iostream"

int main()
{
  auto a = Result<int>::none();
  auto b = Result<int>::some(100);
  auto c = Result<int>::error("hello");

  std::cout << (a.isNone() ? "a is none" : "a is not none") << std::endl;
  std::cout << (b.isSome() ? "b is some" : "a is not some") << std::endl;
  std::cout << (c.isError() ? "c is error" : "c is not error") << std::endl;
  std::cout << "c's error: " << c.error() << std::endl;
  std::cout << "b's value: " << b.get() << std::endl;
  return 0;
}
