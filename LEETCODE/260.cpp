#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
using std::vector;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int AxorB = 0;
        for (auto x: nums) {
            AxorB ^= x;
        }

        int diff_bit = 1;
        while ((diff_bit & AxorB) == 0) {
            diff_bit <<= 1;
        }
        int a = 0;
        int b = 0;
        for (auto x: nums) {
            if ((x & diff_bit) == 0) {
                a ^= x;
            } else {
                b ^= x;
            }
        }
        return {a, b};
    }
};

int main() {
    std::vector<int> nums = {1, 1, 2, 2, 3, 4};
    auto ret = Solution().singleNumber(nums);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
