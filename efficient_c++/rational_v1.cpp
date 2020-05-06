#include "rational_v1.h"

NextOnFreeList* RationalV1::free_list_ = NULL;

void* RationalV1::operator new(unsigned long size)
{
  if (! free_list_)
  {
    expand_free_list();
  }
  NextOnFreeList* ret = free_list_;
  free_list_ = ret->next;
  return ret;
}

void RationalV1::operator delete(void* doomed, unsigned long size)
{
  NextOnFreeList* head = (NextOnFreeList*)doomed;
  head->next = free_list_;
  free_list_ = head;
}

void RationalV1::new_mempool()
{
  expand_free_list();
}

void RationalV1::expand_free_list()
{
  size_t size = sizeof(RationalV1) > sizeof(NextOnFreeList*) ? sizeof(RationalV1) : sizeof(NextOnFreeList*);
  NextOnFreeList* curr = (NextOnFreeList*)(new char[size]);
  free_list_ = curr;
  for (int i=1; i<EXPANSION_SIZE; ++i)
  {
    curr->next =(NextOnFreeList*)(new char[size]);
    curr = curr->next;
  }
  curr->next = NULL;
}

void RationalV1::delete_mempool()
{
  NextOnFreeList* tmp;
  while (free_list_)
  {
    tmp = free_list_->next;
    delete [] (char*)free_list_;
    free_list_ = tmp;
  }
}
