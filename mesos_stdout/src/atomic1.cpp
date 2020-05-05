#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>

std::atomic<int> foo(0);

void set_foo(int x)
{
  foo = x;
}

void print_foo()
{
  while (foo == 0)
  {
    std::this_thread::yield();
  }
  std::cout << "x: " << foo << std::endl;
}
int main()
{
  std::thread print_th(print_foo);
  std::thread set_th(set_foo, 10);
  print_th.join();
  set_th.join();
  return 0;
}

