#include <utility>
#include <iostream>

void overloaded(const int& x)
{
  std::cout << "[lvalue]" << std::endl;
}

void overloaded(int&& x)
{
  std::cout << "[rvalue]" << std::endl;
}

template <class T> void fn(T&& x)
{
  overloaded(x);
  overloaded(std::forward<T>(x));
}

int main()
{
  int i = 10;
  overloaded(std::forward<int>(i));
  overloaded(std::forward<int&>(i));
  overloaded(std::forward<int&&>(i));
  
  fn(i);
  fn(std::move(i));

  return 0;
}

