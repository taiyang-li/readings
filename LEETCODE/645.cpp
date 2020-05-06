#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <numeric>

/*
class Solution {
public:
    std::vector<int> findErrorNums(std::vector<int>& nums) {
        int bits = nums.size();
        char* bitmap = new char[(bits+7)/8];
        std::vector<int> ret(2, 0);
        int index = 0;
        int weight = 0;
        for (auto num: nums) {
            index = (num-1)/8;
            weight = (num-1)%8;
            if (bitmap[index] & (1 << weight)) {
                ret[0] = num;
            }
            bitmap[index] |= 1 << weight;
        }
        for (size_t i=1; i<=nums.size(); ++i) {
            index = (i-1)/8;
            weight = (i-1)%8;
            if ((bitmap[index] & (1 << weight)) == 0) {
                ret[1] = i;
            }
        }
        delete [] bitmap;
        return ret;
    }
};
*/

class Solution {
public:
    std::vector<int> findErrorNums(std::vector<int>& nums) {
        const int len = nums.size() + 1;
        std::vector<int> count(len, 0);
        for (auto num: nums) {
            count[num]++;
        }
        
        int repeat = 0;
        int miss = 0;
        for (int i=1; i<len; ++i) {
            if (nums[i] == 0) miss = i;
            if (nums[i] > 1) repeat = i;
        }

        std::vector<int> ret;
        ret.push_back(repeat);
        ret.push_back(miss);
        return ret;
    }
};



int main() {
    std::vector<int> nums = {1, 2, 2, 4};
    auto ret = Solution().findErrorNums(nums);
    for (auto num: ret) {
        std::cout << num << std::endl;
    }
    return 0;
}
