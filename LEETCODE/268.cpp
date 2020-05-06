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
    int missingNumber(vector<int>& nums) {
        const int n = nums.size() + 1;
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        return n*(n-1)/2 - sum;
    }
};

int main() {
    std::vector<int> nums = {3, 0, 1};
    std::cout << Solution().missingNumber(nums) << std::endl;
    return 0;
}

