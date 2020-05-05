#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int i)
{
  while (!ready);
  for (int i=0; i<1000000; i++);
  if (!winner.test_and_set())
    std::cout << "winner: " << i << std::endl;
}

int main()
{
  std::vector<std::thread> ths;
  for (int i=0; i<10; i++)
    ths.push_back(std::thread(count1m, i));
  ready = true;
  for (int i=0; i<10; i++)
    ths[i].join();
  return 0;
}

