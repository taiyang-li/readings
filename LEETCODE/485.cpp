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
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int start = 0;
        int end = 0;
        const int len = nums.size();
        int ret = 0;
        while (start < len) {
            while (start < len && nums[start] == 0) ++start;
            end = start;
            while (end < len && nums[end] == 1) ++end;

            ret = std::max(ret, end-start);
            start = end;
        }
        return ret;
    }
};

int main() {
    return 0;
}

