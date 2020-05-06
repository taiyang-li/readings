#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class RecentCounter {
public:
    RecentCounter() {}
    
    int ping(int t) {
        _ts.push_back(t);
        if (_ts.size() == 1) {
            _start_idx = 0;
            return 1;
        }

        int lower = std::max(t-3000, 1);
        auto it = std::lower_bound(_ts.begin() + _start_idx, _ts.end(), lower);
        _start_idx = it - _ts.begin();
        return _ts.end() - it;
    }
    
private:
    std::vector<int> _ts;
    size_t _start_idx;
};

int main() {
    RecentCounter* counter = new RecentCounter();
    std::cout << counter->ping(1) << std::endl;
    std::cout << counter->ping(100) << std::endl;
    std::cout << counter->ping(3001) << std::endl;
    std::cout << counter->ping(3002) << std::endl;
    return 0;
}

