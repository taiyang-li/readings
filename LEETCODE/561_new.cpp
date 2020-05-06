#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        ::memset(_bitmap, 0, sizeof(_bitmap));
        for (auto num : nums) {
            _bitmap[num+10000]++;
        }

        int prev = 0;
        int count = 0;
        int ret = 0;
        for (size_t i=0; i<sizeof(_bitmap)/sizeof(uint16_t); ++i) {
            while (_bitmap[i] > 0) {
                count++;
                if (count % 2 == 0) {
                    ret += prev;
                }
                prev = i-10000;
                _bitmap[i]--;
            }
        }
        return ret;
    }

protected:
    uint16_t _bitmap[20001];
};

int main() {
    vector<int> nums = {1, 4, 3, 2};
    std::cout << Solution().arrayPairSum(nums) << std::endl;
    return 0;
}
