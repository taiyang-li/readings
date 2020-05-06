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
    double findMaxAverage(vector<int>& nums, int k) {
        const int len = nums.size();
        int max_sum = std::accumulate(nums.begin(), nums.begin() + k, 0);
        int curr_sum = max_sum;
        for (int i=1; i<=len-k; ++i) {
            curr_sum -= nums[i-1];
            curr_sum += nums[i+k-1];
            max_sum = std::max(max_sum, curr_sum);
        }
        return max_sum/double(k);
    }
}; 

int main() {
    return 0;
}

