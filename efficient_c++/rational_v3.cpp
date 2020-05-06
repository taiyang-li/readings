#include "rational_v3.h"

ByteMemoryPool* RationalV3::mempool_ = NULL;

void* RationalV3::operator new(unsigned long size)
{
  return mempool_->alloc(size);
}

void RationalV3::operator delete(void* doomed, unsigned long size)
{
  mempool_->free(doomed);
}

void RationalV3::new_mempool()
{
  mempool_ = new ByteMemoryPool;
}

void RationalV3::delete_mempool()
{
  delete mempool_;
}
