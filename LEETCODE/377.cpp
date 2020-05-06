#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <iostream>
#include <numeric>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.begin());
        auto it = std::upper_bound(nums.begin(), nums.end(), target);
        const int candidate_num = std::distance(nums.begin(), it);
        if (candidate_num == 0) {
            return 0;
        }
        std::vector<int> coefficient;
        std::vector<std::vector<int> >().swap(_coefficients);
        helper(nums, candidate_num-1, target, coefficient);

        int ret = 0;
        for (const auto& coefficient : _coefficients) {
            ret += combinationOfCoefficient(coefficient);
        }
        return ret;
    }

    inline int combinationOfCoefficient(const std::vector<int>& coefficient) {
        int sum = std::accumulate(coefficient.begin(), coefficient.end(), 0);
        uint64_t ret = fac(sum);
        for (auto x : coefficient) {
            ret /= fac(x);
        }
        return ret;
    }

    static uint64_t fac(int n) {
        int start = _fac_cache.empty() ? 0 : _fac_cache.rbegin()->first;
        uint64_t base = _fac_cache.empty() ? 1 : _fac_cache.rbegin()->second;
        start++;
        for (; start <= n; ++start) {
            base *= start;
            _fac_cache[start] = base;
        }
        return _fac_cache[n];
    }

    void helper(std::vector<int>& nums, int index, int target, std::vector<int>& coefficient) {
        if (index == -1) {
            if (target == 0) {
                _coefficients.push_back(coefficient);
            }
            return;
        }

        for (int i=0; i<=target/nums[index]; ++i) {
            std::vector<int> new_coefficient(coefficient);
            if (i > 0) {
                new_coefficient.push_back(i);
            }
            helper(nums, index-1, target - i * nums[index], new_coefficient);
        } 
    }

protected:
    std::vector<std::vector<int> > _coefficients;
    static std::map<int, uint64_t> _fac_cache;
};
std::map<int, uint64_t> Solution::_fac_cache;

int main() {
    std::vector<int> nums = {1, 2, 3};
    std::cout << Solution().combinationSum4(nums, 4) << std::endl;
    return 0;
}
