#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int ret = 0;
        int sum = 0;
        std::map<int, int> index_by_sum;
        index_by_sum[0] = -1;
        for (int i=0; i<int(nums.size()); ++i) {
            sum += nums[i] == 0 ? -1 : 1;
            auto mit = index_by_sum.find(sum);
            if (mit == index_by_sum.end()) {
                index_by_sum[sum] = i;
            } else {
                ret = std::max(ret, i - mit->second);
            }
        }
        return ret;
    }
};

int main() {
    std::vector<int> nums = {0,1,0};
    std::cout << Solution().findMaxLength(nums) << std::endl;
    return 0;
}
