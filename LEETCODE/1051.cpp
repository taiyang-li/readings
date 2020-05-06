#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
#include <cmath>
#include <set>
#include <stack>
#include <iostream>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    int heightChecker(vector<int>& heights) {
        int ret = 0;
        std::vector<int> sorted_heights(heights.begin(), heights.end());
        std::sort(sorted_heights.begin(), sorted_heights.end());
        for (size_t i=0; i<heights.size(); ++i) {
            if (heights[i] != sorted_heights[i]) {
                ++ret;
            }
        }
        return ret;
    }
}; 

int main() {
    std::vector<int> heights = {1,1,4,2,1,3};
    std::cout << Solution().heightChecker(heights) << std::endl;
    return 0;
}
