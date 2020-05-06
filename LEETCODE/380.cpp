#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>

using namespace std;

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        ::srand(time(NULL));
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        bool ret = (_map.count(val) == 0);
        if (ret) {
            _map[val] = _vec.size();
            _vec.push_back(val);
        }
        return ret;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        bool ret = (_map.count(val) > 0);
        if (ret) {
            size_t pos = _map[val];
            swap(_vec[pos], *(_vec.rbegin()));
            _vec.pop_back();

            _map[_vec[pos]] = pos;
            _map.erase(val);

        }
        return ret;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        if (_vec.empty()) { 
            return -1;
        }
        return _vec[rand() % _vec.size()];
    }
    
protected:
    unordered_map<int, size_t> _map;
    vector<int> _vec;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
int main () {
    RandomizedSet* obj = new RandomizedSet();
    std::cout << obj->remove(0) << std::endl;
    std::cout << obj->remove(0) << std::endl;
    std::cout << obj->insert(0) << std::endl;
    std::cout << obj->getRandom() << std::endl;
    std::cout << obj->remove(0) << std::endl;
    std::cout << obj->insert(0) << std::endl;
    return 0;
}
