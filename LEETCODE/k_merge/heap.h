#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>

enum HeapType {MAX_HEAP = 0, MIN_HEAP}; 

template <class T>
class Heap {
public:
    static Heap<T>* create_heap(std::vector<int>& vec, HeapType type = MIN_HEAP);

    Heap(HeapType type = MIN_HEAP);
    ~Heap();

    T& top();
    void pop();
    void push(const T& val);

    bool empty() const; 
    
protected:
    void fix_down(int idx);
    void fix_up(int idx);
    bool single_fix(int child_idx, int parent_idx);
    size_t find_children_extreme(int parent_idx);

    std::vector<T> _vec;
    size_t _size; 
    HeapType _type;
};

template <class T>
Heap<T>* Heap<T>::create_heap(std::vector<int>& vec, HeapType type) {
    Heap<T>* heap = new Heap<T>(type);
    for (const auto& val: vec) {
        heap->push(val);
    }
    return heap;
}

template <class T>
Heap<T>::Heap(HeapType type): _size(0), _type(type) {}

template <class T>
Heap<T>::~Heap() {}

template <class T>
inline bool Heap<T>::single_fix(int child_idx, int parent_idx) {
    assert(child_idx < _size && parent_idx < _size && child_idx/2 == parent_idx);
    if (_type == MAX_HEAP && _vec[parent_idx] < _vec[child_idx] || 
            _type == MIN_HEAP && _vec[parent_idx] > _vec[child_idx]) {
        std::swap(_vec[child_idx], _vec[parent_idx]);
        return true;
    } else {
        return false;
    }
}

template <class T>
inline size_t Heap<T>::find_children_extreme(int parent_idx) {
    size_t left_idx = parent_idx * 2;
    size_t right_idx = parent_idx * 2 + 1;
    if (right_idx < _size) {
        if (_type == MAX_HEAP) {
            return _vec[left_idx] < _vec[right_idx] ? right_idx : left_idx;
        } else {
            return _vec[left_idx] < _vec[right_idx] ? left_idx : right_idx;
        }
    } else if (left_idx < _size) {
        return left_idx; 
    } else {
        return _size;
    }
}

template <class T>
void Heap<T>::fix_down(int idx) {
    size_t next_idx = find_children_extreme(idx);
    while (idx < _size && next_idx < _size && single_fix(next_idx, idx)){
        idx = next_idx;
        next_idx = find_children_extreme(idx);
    }
}

template <class T>
void Heap<T>::fix_up(int idx) {
    size_t prev_idx = idx/2;
    while (idx > 0 && single_fix(idx, prev_idx)) {
        idx = prev_idx;
        prev_idx = idx/2;
    }
}

template <class T>
T& Heap<T>::top() {
    return _vec[0];
}

template <class T> 
void Heap<T>::pop() {
    std::swap(_vec[0], _vec[_size-1]);
    _size--;
    fix_down(0);
}

template <class T>
void Heap<T>::push(const T& val) {
    if (_vec.size() == _size) {
        _vec.push_back(val);
    } else {
        _vec[_size] = val;
    }
    ++_size;
    fix_up(_size-1);
}

template <class T>
bool Heap<T>::empty() const {
    return _size == 0;
}
