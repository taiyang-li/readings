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
    int dominantIndex(vector<int>& nums) {
        const int len = nums.size();
        if (len == 1) return 0;
        int first = nums[0] > nums[1] ? 0 : 1; 
        int second = nums[0] > nums[1] ? 1 : 0; 
        for (int i=2; i<len; ++i) {
            if (nums[i] > nums[first]) {
                second = first;
                first = i;
            } else if (nums[i] > nums[second]) {
                second = i;
            }
        }
        return nums[first] >= 2 * nums[second] ? first : -1;
    }
};
int main() {
    return 0;
}

