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
    bool increasingTriplet(std::vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        }
        
        int min1 = INT_MAX;
        int min2 = INT_MAX;
        for (int i=0; i<int(nums.size()); ++i) {
            if (nums[i] > min1) {
                if (nums[i] > min2) {
                    return true;
                }
                min2 = std::min(min2, nums[i]);
            } 
            min1 = std::min(min1, nums[i]);
        }
        return false;
    }
};

int main() {
    std::vector<int> nums = {1,2,3,4,5};
    std::vector<int> nums1 = {5,4,3,2,1};
    std::cout << Solution().increasingTriplet(nums) << std::endl;
    std::cout << Solution().increasingTriplet(nums1) << std::endl;
    return 0;
}
