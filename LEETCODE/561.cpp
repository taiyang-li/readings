#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int ret = 0;
        sort(nums.begin(), nums.end());
        
        for (size_t i=0; i<nums.size(); i+=2) {
            ret += nums[i];
        }
        return ret;
    }
};

int main() {
    vector<int> nums = {1, 4, 3, 2};
    std::cout << Solution().arrayPairSum(nums) << std::endl;
    return 0;
}
