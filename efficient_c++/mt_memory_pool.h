#ifndef __EFFICIENT_CPP_MT_MEMORY_POOL_H__
#define __EFFICIENT_CPP_MT_MEMORY_POOL_H__

#include "memory_pool.h"

template <class POOL, class LOCK>
class MTMemoryPool
{
  public:
    MTMemoryPool() {}
    ~MTMemoryPool() {}

    inline void* alloc();
    inline void free(void* element);

  private:
    POOL pool_;
    LOCK lock_;
};

template <class POOL, class LOCK>
inline void* MTMemoryPool<POOL, LOCK>::alloc()
{
  lock_.lock();
  void* ret = pool_.alloc();
  lock_.unlock();
  return ret;
}

template <class POOL, class LOCK>
inline void MTMemoryPool<POOL, LOCK>::free(void* element)
{
  lock_.lock();
  pool_.free(element);
  lock_.unlock();
}

#endif  /*MT_MEMORY_POOL_H*/
