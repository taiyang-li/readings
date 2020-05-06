#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class MyCircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) : _vec(k+1, 0), _size(k+1), _head(0), _tail(0) {}
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        _vec[_tail] = value;
        _tail = (_tail + 1) % _size;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        _vec[_head] = 0;
        _head = (_head + 1) % _size;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return _vec[_head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return _vec[(_tail - 1 + _size) % _size];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return _head == _tail;
    }
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return (_tail + 1 ) % _size == _head;
    }

protected:
    std::vector<int> _vec;
    const int _size;
    int _head;
    int _tail;
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue obj = new MyCircularQueue(k);
 * bool param_1 = obj.enQueue(value);
 * bool param_2 = obj.deQueue();
 * int param_3 = obj.Front();
 * int param_4 = obj.Rear();
 * bool param_5 = obj.isEmpty();
 * bool param_6 = obj.isFull();
 */

int main() {
    MyCircularQueue circularQueue(3);
    std::cout << circularQueue.enQueue(1);  // return true
    std::cout << circularQueue.enQueue(2);  // return true
    std::cout << circularQueue.enQueue(3);  // return true
    std::cout << circularQueue.enQueue(4);  // return false, the queue is full
    std::cout << circularQueue.Rear();  // return 3
    std::cout << circularQueue.isFull();  // return true
    std::cout << circularQueue.deQueue();  // return true
    std::cout << circularQueue.enQueue(4);  // return true
    std::cout << circularQueue.Rear();  // return 4
    return 0;
}
