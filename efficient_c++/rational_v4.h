#ifndef __EFFICIENT_CPP_RATIONAL_V4_H__
#define __EFFICIENT_CPP_RATIONAL_V4_H__

#include <cstdio>
#include <cstring>
#include "mt_memory_pool.h"
#include "memory_pool.h"
#include "my_lock.h"

class RationalV4
{
  public:
    RationalV4(int m=0, int n=1) : m_(m), n_(n) {}
    ~RationalV4() {}

    void* operator new(unsigned long size);
    void operator delete(void *doomed, unsigned long size);

    int m() const {return m_;}
    int n() const {return n_;}
    
    static void new_mempool();
    static void delete_mempool();
    
  private:
    int m_;
    int n_;
    static ::MTMemoryPool<MemoryPool<RationalV4>, ::MyLock>* mempool_;
};

#endif
