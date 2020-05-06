#include <iostream>
#include <cstddef>
#include <mutex>
#include <cassert>

template <class T>
class SharedPtr {
public:
    SharedPtr();
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& other);
    ~SharedPtr();
    
    SharedPtr& operator=(const SharedPtr& other);
    void reset();
    void reset(T* ptr);

    T& operator*() const;
    T* operator->() const;
    T* get() const;
    size_t use_count() const;

private:
    size_t* _count;
    T* _ptr;
    std::mutex _mutex;
};

template <class T>
SharedPtr<T>::SharedPtr(): _count(nullptr), _ptr(nullptr) {}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr): _ptr(ptr) {
    _count = new size_t(1);
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other): _count(other._count), _ptr(other._ptr){
    if (this == &other) {
        return;
    }
    
    {
        std::unique_lock<std::mutex> lock(_mutex);
        if (_count != nullptr) {
            ++(*_count);
        }
    }
}

template <class T>
SharedPtr<T>::~SharedPtr(){
    if (_count == nullptr) {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(_mutex);
        if (--(*_count) == 0) {
            delete _ptr;
            _ptr = nullptr;

            delete _count;
            _count = nullptr;
        }
    }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    if (this == &other) {
        return *this;
    }
    
    if (_count != nullptr) {
        std::unique_lock<std::mutex> lock(_mutex);
        if (--(*_count) == 0) {
            delete _ptr;
            _ptr = nullptr;

            delete _count;
            _count = nullptr;
        }
    }
    _count = other._count;
    _ptr = other._ptr;
    if (_count != nullptr) {
        std::unique_lock<std::mutex> lock(_mutex);
        ++(*_count);
    }
    return *this;
}


template <class T>
void SharedPtr<T>::reset() {
    if (_count != nullptr) {
        std::unique_lock<std::mutex> lock(_mutex);
        if (--(*_count) == 0) {
            delete _ptr;
            _ptr = nullptr;

            delete _count;
            _count = nullptr;
        }
    }
}

template <class T>
void SharedPtr<T>::reset(T* ptr) {
    if (_ptr == ptr) {
        return;
    }

    if (_count != nullptr) {
        std::unique_lock<std::mutex> lock(_mutex);
        if (--(*_count) == 0) {
            delete _ptr;
            _ptr = nullptr;

            delete _count;
            _count = nullptr;
        }
    }

    _ptr = ptr;
    if (ptr != nullptr) {
        _count = new size_t(1);
    }
}

template <class T>
T& SharedPtr<T>::operator*() const {
    assert(_ptr != nullptr);
    return *_ptr;
}

template <class T>
T* SharedPtr<T>::operator->() const {
    assert(_ptr != nullptr);
    return _ptr;
}

template <class T>
T* SharedPtr<T>::get() const {
    return _ptr;
}

template <class T>
size_t SharedPtr<T>::use_count() const {
    if (_count == nullptr) {
        return 0;
    }
    return *_count;
}
