#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // build num to right adjacent num
        std::stack<int> st;
        std::unordered_map<int, int> next_greater;
        for (auto num: nums2) {
            while (! st.empty() && st.top() < num) {
                next_greater[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }

        const int len1 = nums1.size();
        std::vector<int> ret(len1, -1);
        for (int i=0; i<len1; ++i) {
            auto mit = next_greater.find(nums1[i]);
            if (mit != next_greater.end()) {
                ret[i] = mit->second;
            } else {
                ret[i] = -1;
            }
        }
        return ret;
    }
};
int main() {
    return 0;
}

