#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
#include <set>
using namespace std;

struct Entry {
    int key;
    int value;
    uint64_t freq;
    uint64_t epoch;

    Entry(int k=0, int v=0, uint64_t f=0, uint64_t e=0): key(k), value(v), freq(f), epoch(e) {}
    
    friend bool operator<(const Entry& left, const Entry& right) {
        return left.freq < right.freq || (left.freq == right.freq && left.epoch < right.epoch);
    }
};

class LFUCache {
public:
    LFUCache(int capacity) : _capacity(capacity), _epoch(0) {}
    
    int get(int key) {
        auto mit = _indexes.find(key);
        if (mit == _indexes.end()) {
            // std::cout << "returns " << -1 << std::endl;
            return -1;
        }

        int ret = mit->second->value;
        Entry entry = *(mit->second);
        entry.epoch = _epoch++;
        entry.freq++;

        _entries.erase(mit->second);
        auto insert_ret = _entries.insert(entry);
        mit->second = insert_ret.first;
        // std::cout << "returns " << ret << std::endl;
        return ret;
    }
    
    void put(int key, int value) {
        auto mit = _indexes.find(key);
        bool need_evict = mit == _indexes.end() && int(_entries.size()) >= _capacity;
        if (need_evict) {
            if (! evict()) {
                return;
            }
        }

        Entry entry;
        if (mit != _indexes.end()) {
            entry = *(mit->second);
            _entries.erase(mit->second);
            _indexes.erase(key);
        } 
        entry.key = key;
        entry.value = value;
        entry.freq++;
        entry.epoch = _epoch++;

        auto insert_ret = _entries.insert(entry);
        _indexes.insert(std::make_pair(key, insert_ret.first));
    }

    bool evict() {
        if (_entries.empty()) return false;
        int key = _entries.begin()->key;
        _entries.erase(_entries.begin());
        _indexes.erase(key);
        // std::cout << "evict key " << key << std::endl;
        return true;
    }
    
protected:
    std::set<Entry> _entries;
    std::map<int, std::set<Entry>::iterator> _indexes;
    int _capacity;
    uint64_t _epoch;
};

int main() {
    /*
    LFUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);       // returns 1
    cache.put(3, 3);    // evicts key 2
    cache.get(2);       // returns -1 (not found)
    cache.get(3);       // returns 3.
    cache.put(4, 4);    // evicts key 1.
    cache.get(1);       // returns -1 (not found)
    cache.get(3);       // returns 3
    cache.get(4);       // returns 4
    */
    LFUCache cache(0);
    cache.put(0, 0);
    cache.get(0);
    return 0;
}
