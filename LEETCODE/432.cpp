#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <string>
#include <functional>
#include <set>
#include <map>
using namespace std;

struct Item {
    std::string key;
    int value;
    Item(const std::string& k, int v): key(k), value(v) {}
};

class CmpByItem {
    public:
        bool operator()(const Item& left, const Item& right) {
            if (left.value < right.value) {
                return true;
            } else if (left.value == right.value) {
                return std::less<std::string>()(left.key, right.key);
            } else {
                return false;
            }
        }
};
class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (_map.count(key) > 0) {
            _items.erase(Item(key, _map[key]));
        } 
        _map[key]++;
        _items.insert(Item(key, _map[key]));
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (_map.count(key) == 0) {
            return;
        }
        
        _items.erase(Item(key, _map[key]));
        _map[key]--;
        if (_map[key] == 0) {
            _map.erase(key);
        } else {
            _items.insert(Item(key, _map[key]));
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (_items.empty()) {
            return "";
        }
        return _items.rbegin()->key;
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (_items.empty()) {
            return "";
        }
        return _items.begin()->key;
    }
    
protected:
    std::set<Item, CmpByItem> _items;
    std::map<std::string, int> _map;
};

int main() {
    AllOne obj;
    obj.inc("foo");
    obj.inc("foo");
    obj.inc("bar");
    obj.inc("bar");
    obj.dec("foo");
    obj.dec("bar");
    std::cout << obj.getMaxKey() << std::endl;
    std::cout << obj.getMinKey() << std::endl;
    return 0;
}
