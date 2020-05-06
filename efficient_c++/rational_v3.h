#ifndef __EFFICIENT_CPP_RATIONAL_V3_H__
#define __EFFICIENT_CPP_RATIONAL_V3_H__

#include <cstdio>
#include <cstring>
#include "byte_memory_pool.h"

class RationalV3
{
  public:
    RationalV3(int m=0, int n=1) : m_(m), n_(n) {}
    ~RationalV3() {}

    void* operator new(unsigned long size);
    void operator delete(void *doomed, unsigned long size);

    int m() const {return m_;}
    int n() const {return n_;}
    
    static void new_mempool();
    static void delete_mempool();
    
  private:
    int m_;
    int n_;
    static ::ByteMemoryPool* mempool_;
};

#endif
