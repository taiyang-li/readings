#ifndef __EFFICIENT_CPP_MEMORY_CHUNK_H__
#define __EFFICIENT_CPP_MEMORY_CHUNK_H__

#include <cstdio>
#include <algorithm>

class MemoryChunk
{
  public:
    MemoryChunk(size_t size=DEFAULT_CHUNK_SIZE)
      : next_(NULL), used_size_(0)
    {
      total_size_ = std::max((size_t)DEFAULT_CHUNK_SIZE, size);
      chunk_ = new char[total_size_];
    }

    ~MemoryChunk()
    {
      delete [] (char*)chunk_;
    }

    MemoryChunk* next() const
    {
      return next_;
    }

    MemoryChunk*& next()
    {
      return next_;
    }

    size_t free_size() const
    {
      return total_size_ - used_size_;
    }

    inline void* alloc(size_t size)
    {
      if (size > free_size())
        return NULL;
      void* addr = (void*)((char*)chunk_ + used_size_);
      used_size_ += size;
      return addr;
    }

    void free(void* element) {}

    enum {DEFAULT_CHUNK_SIZE=4096};

  private:
    MemoryChunk* next_;
    void* chunk_;
    size_t total_size_;
    size_t used_size_;

};

#endif  /*MEMORY_CHUNK_H*/
