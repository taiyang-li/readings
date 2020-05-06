#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <sstream>
#include <functional>
#include <cstdint>
#include <random>
using namespace std;

template <typename T>
struct Entry {
    T val;
    Entry* next;
    
    Entry(const T& v=T(), Entry* n=NULL) : val(v), next(n) {}
};

typedef std::function<size_t (int)> HashFunc;
typedef Entry<int>* EntryPtr;
typedef Entry<int>** EntryPtrPtr;

class MyHashSet {
public:
    /** Initialize your data structure here. */
    MyHashSet(const HashFunc& hash_func=std::hash<int>()) : _in_use(0), _size(4), _used(0), 
        _factor(1.0), _hash_func(hash_func) {
        _tables[_in_use] = new EntryPtr[_size];
        _tables[1-_in_use] = NULL;
        EntryPtrPtr table = _tables[_in_use];
        for (size_t i=0; i<_size; ++i) {
            table[i] = NULL;
        }
    }
    
    virtual ~MyHashSet() {
        for (size_t i=0; i<_size; ++i) {
            while (_tables[_in_use][i] != NULL) {
                EntryPtr entry = _tables[_in_use][i];
                _tables[_in_use][i] = entry->next;
                delete entry;
            }
        }
        delete [] _tables[_in_use];
        _tables[_in_use] = NULL;
    }

    void add(int key) {
        size_t hash = _hash_func(key);
        size_t index = hash % _size;
        EntryPtr curr = _tables[_in_use][index];
        while (curr != NULL) {
            if (curr->val == key) {
                return;
            }
            curr = curr->next;
        }

        if (double(1+_used)/_size < _factor || _size >= 4294967296L) {
            EntryPtr entry = new Entry<int>(key, NULL);
            entry->next = _tables[_in_use][index];
            _tables[_in_use][index] = entry;
            _used++;
            return;
        }
        rehash();
        add(key);
    }

    void remove(int key) {
        size_t hash = _hash_func(key);
        size_t index = hash % _size;
        EntryPtrPtr curr = &_tables[_in_use][index];
        while (*curr != NULL) {
            EntryPtr entry = *curr;
            if (entry->val == key) {
                *curr = entry->next;
                delete entry;
                _used++;
                return;
            }
            curr = &entry->next;
        }
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        size_t hash = _hash_func(key);
        size_t index = hash % _size;
        EntryPtr curr = _tables[_in_use][index];
        while (curr != NULL) {
            if (curr->val == key) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    
    void rehash() {
        size_t new_size = _size * 2;
        _tables[1-_in_use] = new EntryPtr[new_size];
        for (size_t i=0; i<new_size; ++i) {
            _tables[1-_in_use][i] = NULL;
        }
        for (size_t i=0; i<_size; ++i) {
            while (_tables[_in_use][i] != NULL) {
                EntryPtr entry = _tables[_in_use][i];

                // 在新的hashtable中插入新节点
                size_t hash = _hash_func(entry->val);
                size_t index = hash % new_size;
                EntryPtr new_entry = new Entry<int>(entry->val, NULL);
                new_entry->next = _tables[1-_in_use][index];
                _tables[1-_in_use][index] = new_entry;

                // 在旧的hashtable中杀出旧节点
                _tables[_in_use][i] = entry->next;
                delete entry;
            }
        }
        delete [] _tables[_in_use];
        _tables[_in_use] = NULL;
        
        _size = new_size;
        _in_use = 1 - _in_use;
    }

    std::string to_string() {
        std::ostringstream oss;
        oss << "in_use:" << _in_use
            << ",size:" << _size 
            << ",used:" << _used << std::endl;
        for (size_t i=0; i<_size; ++i) {
            oss << i << ":";
            EntryPtr curr = _tables[_in_use][i];
            while (curr != NULL) {
                oss << curr->val << "|";
                curr = curr->next;
            }
            oss << std::endl;
        }
        return oss.str();
    }

protected:
    EntryPtrPtr _tables[2];
    int _in_use;
    size_t _size;
    size_t _used;
    const double _factor;
    HashFunc _hash_func;
};

int main() {
    MyHashSet hashSet = MyHashSet();
    for (int i=0; i<100; ++i) {
        int v = rand() % 100;
        std::cout << "------------------------------ insert " << v << " ------------------------------" << std::endl;
        hashSet.add(v);
        std::cout << hashSet.to_string() << std::endl;
    }
    return 0;
}
