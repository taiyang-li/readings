#include "rational_v2.h"

MemoryPool<RationalV2>* RationalV2::mempool_ = NULL;

void* RationalV2::operator new(unsigned long size)
{
  return mempool_->alloc();
}

void RationalV2::operator delete(void* doomed, unsigned long size)
{
  mempool_->free(doomed);
}

void RationalV2::new_mempool()
{
  mempool_ = new MemoryPool<RationalV2>;
}

void RationalV2::delete_mempool()
{
  delete mempool_;
}
