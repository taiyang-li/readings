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
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        int max_len = 1;
        int curr_len = 1;
        int prev = nums[0];
        for (auto it = nums.begin()+1; it != nums.end(); ++it) {
            if (*it > prev) {
                curr_len++;
            } else {
                max_len = std::max(max_len, curr_len);
                curr_len = 1;
            }
            prev = *it;
        }
        max_len = std::max(max_len, curr_len);
        return max_len;
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 4, 7};
    std::cout << Solution().findLengthOfLCIS(nums) << std::endl;
    return 0;
}
