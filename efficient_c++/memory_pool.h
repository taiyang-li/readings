#ifndef __EFFICIENT_CPP_MEMORY_POOL_H__
#define __EFFICIENT_CPP_MEMORY_POOL_H__

#include <cstdio>
#include "freelist.h"

template <class T>
class MemoryPool
{
  public:
    MemoryPool(size_t count=EXPANSION_SIZE);
    ~MemoryPool();

    inline void* alloc();
    inline void free(void* element);

  private:
    void expand_free_list(size_t count=EXPANSION_SIZE);

    enum { EXPANSION_SIZE=32 };
    NextOnFreeList* free_list_;
};

template <class T>
MemoryPool<T>::MemoryPool(size_t count) 
  : free_list_(NULL)
{
  expand_free_list(count);
}

template <class T>
MemoryPool<T>::~MemoryPool()
{
  NextOnFreeList* tmp;
  while (free_list_)
  {
    tmp = free_list_->next;
    delete [] (char*)free_list_;
    free_list_ = tmp;
  }
}

template <class T>
inline void* MemoryPool<T>::alloc()
{
  if (! free_list_)
  {
    expand_free_list(EXPANSION_SIZE);
  }
  NextOnFreeList* ret = free_list_;
  free_list_ = ret->next;
  return ret;
}

template <class T>
inline void MemoryPool<T>::free(void* element)
{
  NextOnFreeList* head = (NextOnFreeList*)element;
  head->next = free_list_;
  free_list_ = head;
}

template <class T>
void MemoryPool<T>::expand_free_list(size_t count)
{
  size_t size = sizeof(T) > sizeof(NextOnFreeList*) ? sizeof(T) : sizeof(NextOnFreeList*);
  NextOnFreeList* curr = (NextOnFreeList*)(new char[size]);
  free_list_ = curr;
  for (int i=1; i<int(count); ++i)
  {
    curr->next =(NextOnFreeList*)(new char[size]);
    curr = curr->next;
  }
  curr->next = NULL;
}

#endif  /*MEMORY_POOL_H*/
