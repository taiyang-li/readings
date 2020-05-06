#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        const int n = nums.size();
        if (n <= 1) return 0;
        
        long S = 0;
        for (auto num : nums) {
            S += num;
        }
        long k = std::ceil(-S/double(n));
        for (auto num : nums) {
            long tmp1 = std::ceil(-num);
            long tmp2 = std::ceil((num-S)/double(n-1));
            k = std::max(k, tmp1);
            k = std::max(k, tmp2);
        }
        return S + n * k;
    }
};

int main() {
    std::vector<int> nums = {1,1,2147483647};
    std::cout << Solution().minMoves(nums) << std::endl;
    return 0;
}
