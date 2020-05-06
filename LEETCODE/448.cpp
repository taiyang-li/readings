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
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        std::vector<int> ret(nums.size(), 0);
        for (auto num : nums) {
            ret[num-1] = 1;
        }
        int count = 0;
        for (size_t i=0; i<ret.size(); ++i) {
            if (ret[i] == 0) {
                ret[count++] = i+1;
            }
        }
        ret.resize(count);
        return ret;
    }
};

int main() {
    std::vector<int> nums = {4,3,2,7,8,2,3,1};
    auto ret = Solution().findDisappearedNumbers(nums);
    for (auto x : ret ) {
        std::cout << x << std::endl;
    }
    return 0;
}
