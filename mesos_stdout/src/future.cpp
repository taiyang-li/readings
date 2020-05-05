#include <future>
#include <iostream>
#include <stout/stringify.hpp>

bool is_prime(int x)
{
  for (int i=0; i<x; i++)
  {
    if (x % i == 0)
      return false;
  }
  return true;
}

int main()
{
  std::future<bool> fut = std::async(is_prime, 700020007);
  std::cout << "please wait";
  std::chrono::milliseconds span(100);
  while (fut.wait_for(span) != std::future_status::ready)
    std::cout << ".";
  std::cout << std::endl;

  bool ret = fut.get();
  std::cout << "final result: " << stringify(ret) << std::endl;
  return 0;
}
