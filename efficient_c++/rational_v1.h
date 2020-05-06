#ifndef __EFFICIENT_CPP_RATIONAL_V1_H__
#define __EFFICIENT_CPP_RATIONAL_V1_H__

#include <cstdio>
#include <cstring>
#include "freelist.h"

class RationalV1
{
  public:
    RationalV1(int m=0, int n=1) : m_(m), n_(n) {}
    ~RationalV1() {}

    void* operator new(unsigned long size);
    void operator delete(void *doomed, unsigned long size);

    int m() const {return m_;}
    int n() const {return n_;}
    
    static void new_mempool();
    static void delete_mempool();
    
  private:
    int m_;
    int n_;

    static NextOnFreeList* free_list_;
    static void expand_free_list();
    enum { EXPANSION_SIZE=32 };
};

#endif
