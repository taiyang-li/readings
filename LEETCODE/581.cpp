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
        int findUnsortedSubarray(vector<int>& nums) {
            if (nums.size() < 2) {
                return 0;
            }

            const int len = nums.size();
            int left = 0;
            while (left < len) {
                if (left + 1 < len && nums[left] <= nums[left+1]) {
                    left++;
                } else {
                    break;
                }
            }
            if (left == len-1) {
                return 0;
            }

            int right = len-1;
            while (right >= 0) {
                if (right > 0 && nums[right-1] <= nums[right]) {
                    right--;
                } else {
                    break;
                }
            }
            int min_value = nums[left];
            int max_value = nums[right];
            for (int i=left; i<=right; ++i) {
                min_value = std::min(min_value, nums[i]);
                max_value = std::max(max_value, nums[i]);
            }
            auto lower_bound = std::upper_bound(nums.begin(), nums.begin() + left, min_value);
            auto upper_bound = std::lower_bound(nums.begin() + right + 1, nums.end(), max_value);
            return upper_bound - lower_bound;
        }
};

int main() {
    std::vector<int> nums = {1,3,5,4,2};
    std::cout << Solution().findUnsortedSubarray(nums) << std::endl;
    return 0;
}
