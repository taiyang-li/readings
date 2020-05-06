#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
#include <set>
using namespace std;

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        std::map<int, int> frequencies;
        std::map<int, std::pair<int, int> > ranges;
        for (size_t i=0; i<nums.size(); ++i) {
            frequencies[nums[i]]++;
            auto it = ranges.find(nums[i]);

            if (it == ranges.end()) {
                ranges[nums[i]] = std::pair<int, int>(i, i);
            } else {
                ranges[nums[i]].second = i;
            }
        }
        
        int max_frequency = 1;
        std::set<int> most_frequency_nums;
        for (auto kv : frequencies) {
            if (kv.second == max_frequency) {
                most_frequency_nums.insert(kv.first);
            } else if (kv.second > max_frequency) {
                max_frequency = kv.second;
                most_frequency_nums.clear();
                most_frequency_nums.insert(kv.first);
            }
        }

        int ret = nums.size();
        for (auto num : most_frequency_nums) {
            ret = std::min(ret, ranges[num].second - ranges[num].first + 1);
        }
        return ret;
    }
};

int main() {
    // vector<int> nums = {1, 2, 2, 3, 1};
    vector<int> nums = {1,2,2,3,1,4,2};
    std::cout << Solution().findShortestSubArray(nums) << std::endl;
    return 0;
}
