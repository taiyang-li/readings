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

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        sstd::sort(nums.begin(), nums.end());
        const int len = nums.size();
        return std::max(nums[0] * nums[1] * nums[len-1], nums[len-2] * nums[len-1] * nums[len-3]);
    }
};
int main() {
    return 0;
}

