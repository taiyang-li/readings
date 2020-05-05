#include <utility>
#include <iostream>
#include <string>
#include <vector>

void foo(const std::string& n)
{
  std::cout << "lvalue" << std::endl;
}

void foo(std::string&& n)
{
  std::cout << "rvalue" << std::endl;
}

void bar()
{
  foo("hello");                // rvalue
  std::string a = "world";      
  foo(a);                      // lvalue
  foo(std::move(a));           // rvalue
}

int main()
{
  std::vector<std::string> a = {"hello", "world"};
  std::vector<std::string> b;

  b.push_back("hello");
  b.push_back(std::move(a[1]));

  std::cout << "bsize: " << b.size() << std::endl;
  for (std::string& x: b)
    std::cout << x << std::endl;
  bar();
  return 0;
}
