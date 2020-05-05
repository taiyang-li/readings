#include <iostream>
#include <atomic>
#include <thread>

std::atomic<bool> ready(false);

void count1m(int id)
{
  while(!ready)
  {
    std::this_thread::yield();
  }
  for(volatile int i=0; i<1000000; i++);
  std::cout << id;
}

int main()
{
  /*
  std::thread th[10];
  std::cout << "start 10 threads" << std::endl;
  for (int i=0; i<10; i++)
    th[i] = std::thread(count1m, i);
  ready = true;
  for (int i=0; i<10; i++)
    th[i].join();
  */
  while (1)
    std::this_thread::yield();
  return 0;
}
