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
    void moveZeroes(vector<int>& nums) {
        int left = -1;
        for (auto num: nums) {
            if (num != 0) {
                nums[++left] = num;
            }
        }
        for (int i=left+1; i<nums.size(); ++i) {
            nums[i] = 0;
        }
    }
};

int main() {
    return 0;
}

