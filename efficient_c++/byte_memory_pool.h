#ifndef __EFFICIENT_CPP_BYTE_MEMORY_POOL_H__
#define __EFFICIENT_CPP_BYTE_MEMORY_POOL_H__

#include "memory_chunk.h"

class ByteMemoryPool
{
  public:
    ByteMemoryPool(size_t init_size=MemoryChunk::DEFAULT_CHUNK_SIZE)
      : chunk_list_(NULL)
    {
      expand_storage(init_size);
    }

    ~ByteMemoryPool()
    {
      ::MemoryChunk* tmp = NULL;
      while (chunk_list_)
      {
        tmp = chunk_list_->next();
        delete chunk_list_;
        chunk_list_ = tmp;
      }
    }

    void* alloc(size_t size)
    {
      if (! chunk_list_ || chunk_list_->free_size() < size)
        expand_storage(size);
      return chunk_list_->alloc(size);
    }

    void free(void* element)
    {
      if (! chunk_list_)
        return;
      return chunk_list_->free(element);
    }

  private:
    void expand_storage(size_t size)
    {
      MemoryChunk* head = new MemoryChunk(size);
      head->next() = chunk_list_;
      chunk_list_ = head;
    }

  private:
    ::MemoryChunk* chunk_list_;
};

#endif  /*BYTE_MEMORY_POOL_H*/
