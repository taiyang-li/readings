#include <utility>
#include <iostream>

void bar(const int& x)
{
  std::cout << "lvalue" << std::endl;
}

void bar(int&& x)
{
  std::cout << "rvalue" << std::endl;
}

template <typename T>
void foo(T&& x)
{
  bar(x);
  bar(std::forward<T>(x));
}

int main()
{
  int x = 10;
  foo(x);
  foo(10);
  return 0;
}

