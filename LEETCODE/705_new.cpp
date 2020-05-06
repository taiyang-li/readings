#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class MyHashSet {
public:
    /** Initialize your data structure here. */
    MyHashSet() : _data(1000001, false) {}

    void add(int key) {
        _data[key] = true;
    }

    void remove(int key) {
        _data[key] = false;
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return _data[key];
    }

protected:
    std::vector<bool> _data;
};

int main() {
    return 0;
}
