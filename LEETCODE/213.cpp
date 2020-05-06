#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    int helper(std::vector<int>& nums, int start,  int end) {
        if (start > end) {
            return 0;
        }

        const int len = nums.size();
        std::vector<std::pair<int, int> > table(len, std::make_pair(0, 0));
        table[start].first = nums[start];
        table[start].second = 0;
        for (int i=start+1; i<=end; ++i) {
            table[i].first = table[i-1].second + nums[i];
            table[i].second = std::max(table[i-1].first, table[i-1].second);
        }
        return std::max(table[end].first, table[end].second);
    }

    int rob(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        // 首元素选中
        const int len = nums.size();
        int ret = std::max(nums[0] + helper(nums, 2, len-2), helper(nums, 1, len-1));
        return ret;
    }

};

int main() {
    std::vector<int> nums = {1,2,3,1};
    std::cout << Solution().rob(nums) << std::endl;
    return 0;
}
