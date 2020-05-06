#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <iostream>
#include <numeric>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int combinationSum4(std::vector<int>& nums, int target) {
        if (nums.empty()) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());
        std::vector<int> dp(target+1, 0);
        dp[0] = 1;
        for (int i=nums[0]; i<=target; ++i) {
            for (auto num : nums) {
                if (num > i) {
                    break;
                }
                dp[i] += dp[i - num];
            }
        }
        return dp[target];
    }
};

int main() {
    std::vector<int> nums = {2, 1, 3};
    std::cout << Solution().combinationSum4(nums, 4) << std::endl;
    return 0;
}
