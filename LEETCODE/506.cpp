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
    vector<string> findRelativeRanks(vector<int>& nums) {
        const int len = nums.size();
        std::vector<std::string> ret(len);
        std::map<int, int> m;
        for (int i=0; i<len; ++i) {
            m[nums[i]] = i;
        }
        
        int idx = 0;
        for (const auto& pair: m) {
            if (idx == len-1)
                ret[pair.second] = "Gold Medal";
            else if (idx == len-2)
                ret[pair.second] = "Silver Medal";
            else if (idx == len-3)
                ret[pair.second] = "Bronze Medal";
            else 
                ret[pair.second] = std::to_string(len-idx);
            ++idx;
        }
        return ret;
    }
};
int main() {
    std::vector<int> nums = {5,4,3,2,1};
    auto ret = Solution().findRelativeRanks(nums) ;
    return 0;
}

