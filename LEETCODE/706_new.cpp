#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <sstream>
using namespace std;

class MyHashMap {
public:
    MyHashMap() {
        _data = new int[1000000+1];
        for (int i=0; i<=1000000; ++i) {
            _data[i] = -1;
        }
    }

    ~MyHashMap() {
        delete [] _data;
        _data = NULL;
    }
    
    void put(int key, int value) {
        _data[key] = value;
    }

    void remove(int key) {
        _data[key] = -1;
    }

    /** Returns true if this set contains the specified element */
    int get(int key) {
        return _data[key];
    }
    
protected:
    int* _data;
};

int main() {
    MyHashMap hashSet = MyHashMap();
    for (int i=0; i<100; ++i) {
        int v = rand() % 100;
        std::cout << "------------------------------ insert " << v << "," << i << " ------------------------------" << std::endl;
        hashSet.put(v, i);
    }
    return 0;

}
