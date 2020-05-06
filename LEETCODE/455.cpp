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
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if (s.empty()) return 0;
        int ret = 0;
        int last_index = -1;
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());
        for (auto size: g) {
            auto it = std::lower_bound(s.begin() + last_index + 1, s.end(), size);
            if (it != s.end()) {
                last_index = it - s.begin();
                ++ret;
            } else {
                break;
            }
        }
        return ret;
    }
};

int main() {
    std::vector<int> g = {1,2,3};
    std::vector<int> s = {};
    std::cout << Solution().findContentChildren(g, s) << std::endl;
    return 0;
}

