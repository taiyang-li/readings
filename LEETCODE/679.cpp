#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        do {
            /*
            for (auto num : nums) {
                std::cout << num << " ";
            }
            */
            std::cout << std::endl;
            auto results = doJudgePoint24(nums);
            for (auto result : results) {
                if (equal(result, 24)) {
                    // std::cout << "find" << std::endl;
                    return true;
                }
            }
        } while (std::next_permutation(nums.begin(), nums.end()));
        return false;
    }

    set<double> doJudgePoint24(vector<int>& nums) {
        if (nums.empty()) {
            return set<double>();
        }
        if (nums.size() == 1) {
            return set<double>(nums.begin(), nums.end());
        }

        set<double> ret;
        for (int split=1; split<=int(nums.size()-1); ++split) {
            std::vector<int> left_nums(nums.begin(), nums.begin() + split);
            auto left_ret = doJudgePoint24(left_nums);
            
            std::vector<int> right_nums(nums.begin() + split, nums.end());
            auto right_ret = doJudgePoint24(right_nums);

            for (auto left : left_ret) {
                for (auto right : right_ret) {
                    ret.insert(left + right);
                    ret.insert(left - right);
                    ret.insert(left * right);
                    if (! equal(right, 0)) {
                        ret.insert(left/right);
                    }
                }
            }
        }
        return ret;
    }

    inline bool equal(double d, int i) {
        return std::abs(d-i) < 1e-8;
    }
};

int main() {
    std::vector<int> nums = {7,6,7,5};
    std::cout << Solution().judgePoint24(nums);
    return 0;
}
