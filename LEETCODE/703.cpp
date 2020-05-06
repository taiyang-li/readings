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
#include <queue>
#include <functional>
using std::vector;
using std::string;

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : 
        _k(k),
        _pq(nums.begin(), nums.end()) { }
    
    int add(int val) {
        _pq.push(val);
        int size = _pq.size();
        for (int i=size; i>_k; --i) {
            _pq.pop();
        }
        return _pq.top();
    }

private:
    int _k;
    std::priority_queue<int, std::vector<int>, std::greater<int> > _pq;
};


int main() {
    std::vector<int> nums = {1,2,3,4};
    KthLargest kl(4, nums);
    return 0;
}

