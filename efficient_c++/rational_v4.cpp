#include "rational_v4.h"

::MTMemoryPool<MemoryPool<RationalV4>, ::MyLock>* RationalV4::mempool_ = NULL;

void* RationalV4::operator new(unsigned long size)
{
  return mempool_->alloc();
}

void RationalV4::operator delete(void* doomed, unsigned long size)
{
  mempool_->free(doomed);
}

void RationalV4::new_mempool()
{
  mempool_ = new ::MTMemoryPool<MemoryPool<RationalV4>, ::MyLock>;
}

void RationalV4::delete_mempool()
{
  delete mempool_;
}
