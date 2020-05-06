#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    std::vector<int>::const_iterator _iter;
    const std::vector<int>::const_iterator _end_iter;
public:
	Iterator(const vector<int>& nums): _iter(nums.begin()), _end_iter(nums.end()) {}
	Iterator(const Iterator& iter): _iter(iter._iter), _end_iter(iter._end_iter) {}
	virtual ~Iterator() {}
	// Returns the next element in the iteration.
	int next() {
        if (_iter == _end_iter) {
            return -1;
        }
        int ret = *_iter;
        _iter++;
        return ret;
    }

	// Returns true if the iteration has more elements.
	bool hasNext() const {
        return _iter != _end_iter;
    }
};


class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
        _peek_iter = new Iterator(nums);
	}
    
    virtual ~PeekingIterator() {
        delete _peek_iter;
        _peek_iter = NULL;
    }

    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        if (! _peek_iter->hasNext()) {
            return -1;
        }
        int ret = _peek_iter->next();
        delete _peek_iter;
        _peek_iter = new Iterator(static_cast<Iterator>(*this));
        return ret;
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
        if (! Iterator::hasNext()) {
            return -1;
        }
        int ret = Iterator::next();
        _peek_iter->next();
        return ret;
	}

	bool hasNext() const {
        return Iterator::hasNext();
	}

protected:
    Iterator* _peek_iter;
};

int main() {
    std::vector<int> nums = {1,2,3};
    PeekingIterator pit(nums);
    std::cout << pit.next() << std::endl;
    std::cout << pit.peek() << std::endl;
    std::cout << pit.next() << std::endl;
    std::cout << pit.next() << std::endl;
    std::cout << pit.hasNext() << std::endl;
    return 0;
}
