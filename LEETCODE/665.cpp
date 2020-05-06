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
    bool checkPossibility(vector<int>& nums) {
        const int len = nums.size();
        int rev_count = 0;
        for (int i=1; i<len && rev_count <= 1; ++i) {
            if (nums[i-1] > nums[i]) {
                ++rev_count;
                if (i-2 < 0 || nums[i-2] < nums[i]) nums[i-1] = nums[i];
                else nums[i] = nums[i-1];
            }
        }
        return rev_count <= 1;
    }
};

int main() {
    std::vector<int> nums = {2,3,3,2,4};
    std::cout << Solution().checkPossibility(nums) << std::endl;
    return 0;
}

