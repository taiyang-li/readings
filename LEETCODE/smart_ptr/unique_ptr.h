#include <iostream>
#include <cstddef>
#include <mutex>
#include <cassert>

template <class T>
class UniquePtr {
public:
    UniquePtr();
    UniquePtr(T* ptr);
    UniquePtr(UniquePtr& other);
    ~UniquePtr();
    
    UniquePtr& operator=(UniquePtr& other);
    void reset();
    void reset(T* ptr);
    T& operator*() const;
    T* operator->() const;
    T* get() const;
    T* release();

private:
    T* _ptr;
};

template <class T>
UniquePtr<T>::UniquePtr(): _ptr(nullptr) {}

template <class T>
UniquePtr<T>::UniquePtr(T* ptr): _ptr(ptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>& other): _ptr(other.release()) {}

template <class T>
UniquePtr<T>::~UniquePtr() {
    reset();
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>& other) {
    reset(other.release());
    return *this;
}

template <class T>
void UniquePtr<T>::reset() {
    if (_ptr != nullptr) {
        delete _ptr;
        _ptr = nullptr;
    }
}

template <class T>
void UniquePtr<T>::reset(T* ptr) {
    reset();
    _ptr = ptr;
}

template <class T>
T& UniquePtr<T>::operator*() const {
    assert(_ptr != nullptr);
    return *_ptr;
}

template <class T>
T* UniquePtr<T>::operator->() const {
    assert(_ptr != nullptr);
    return _ptr;
}

template <class T>
T* UniquePtr<T>::get() const {
    return _ptr;
}

template <class T>
T* UniquePtr<T>::release() {
    T* tmp = _ptr;
    _ptr = nullptr;
    return tmp;
}
