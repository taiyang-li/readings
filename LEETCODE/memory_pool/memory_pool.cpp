#include <cstdlib>
#include <stdexcept>
#include <cstddef>
#include <algorithm>

struct NextOnFreeList {
    NextOnFreeList* next;
};

template <class T>
class MemoryPool {
public:
    MemoryPool(size_t capacity);
    ~MemoryPool();
    
    void* alloc();
    void free(void* element);

protected:
    void expand_freelist(size_t capacity);

    size_t _capacity;
    NextOnFreeList* _freelist;
};

template <class T>
MemoryPool<T>::MemoryPool(size_t capacity): 
    _capacity(capacity), _freelist(nullptr) {
    if (_capacity == 0) {
        throw std::runtime_error("capacity = 0");
    }
    expand_freelist(_capacity);
}

template <class T>
MemoryPool<T>::~MemoryPool() {
    NextOnFreeList* curr = _freelist;
    while (curr != nullptr) {
        NextOnFreeList* next = curr->next;
        free(curr);
        curr = next;
    }
} 

template <class T>
void* MemoryPool<T>::alloc() {
    if (_freelist == nullptr) {
        return nullptr;
    }
    NextOnFreeList* ret = _freelist;
    _freelist = _freelist->next;
    return ret;
}

template <class T>
void MemoryPool<T>::free(void* element) {
    if (element == nullptr) {
        throw std::runtime_error("free nullptr");
    }
    NextOnFreeList* head = (NextOnFreeList*)element;
    head->next = _freelist;
    _freelist = head;
}

template <class T> 
void MemoryPool<T>::expand_freelist(size_t capacity) {
    size_t size = std::max(sizeof(NextOnFreeList*), sizeof(T));
    NextOnFreeList* curr = (NextOnFreeList*) malloc(size);
    if (curr == nullptr) {
        throw std::runtime_error("malloc failed");
    }
    _freelist = curr;
    for (size_t i=1; i<capacity; ++i) {
        NextOnFreeList* next = (NextOnFreeList*) malloc(size);
        if (next == nullptr) {
            throw std::runtime_error("malloc failed");
        }
        curr->next = next;
        curr = next;
    }
}

int main() {
    MemoryPool<int> pool(1024);
    for (int i=0; i<100000; ++i) {
        for (int j=0; j<1024; ++j) {
            int* a = (int*)pool.alloc();
            *a = i + j;
            pool.free((void*)a);
        }
    }
    return 0;
}

