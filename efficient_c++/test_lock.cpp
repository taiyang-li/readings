#include <pthread.h>
#include <functional>
#include "lock.h"
#include "benchmark.h"

void test_lock_v0()
{
  ::pthread_mutex_t mutex;
  ::pthread_mutex_init(&mutex, NULL);
  size_t count = 0;
  for (size_t i=0; i<1000000; ++i)
  {
    ::pthread_mutex_lock(&mutex);
    count++;
    ::pthread_mutex_unlock(&mutex);
  }
}

void test_lock_v1()
{
  ::pthread_mutex_t mutex;
  ::pthread_mutex_init(&mutex, NULL);
  size_t count = 0;
  for (size_t i=0; i<1000000; ++i)
  {
    Lock lock(mutex);
    count++;
  }
}

void test_lock_v2()
{
  ::pthread_mutex_t mutex;
  ::pthread_mutex_init(&mutex, NULL);
  size_t count = 0;
  for (size_t i=0; i<1000000; ++i)
  {
    MutexLock mlock(mutex);
    count++;
  }
}

int main()
{
  ::Benchmark(std::bind(test_lock_v0), "test_lock_v0", 10);
  ::Benchmark(std::bind(test_lock_v1), "test_lock_v1", 10);
  ::Benchmark(std::bind(test_lock_v2), "test_lock_v2", 10);
  return 0;
}
