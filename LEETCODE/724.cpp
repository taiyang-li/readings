#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <numeric>

class Solution {
public:
    int pivotIndex(std::vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }

        if (nums.size() == 1) {
            return 0;
        }

        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int left_sum = 0;
        for (size_t i=0; i<nums.size(); ++i) {
            if (2*left_sum + nums[i] == sum) {
                return i;
            }
            left_sum += nums[i];
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {1, 7, 3, 6, 5, 6};
    std::cout << Solution().pivotIndex(a) << std::endl;

    std::vector<int> b = {1, 2, 3};
    std::cout << Solution().pivotIndex(b) << std::endl;
    
    return 0;
}
