#include <iostream>

void foo(int x)
{
  std::cout << "int" << std::endl;
}

void foo(int* x)
{
  std::cout << "int*" << std::endl;
}

int main()
{
  foo(nullptr);
  foo(NULL);
  return 0;
}

