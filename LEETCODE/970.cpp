#include <iostream>
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
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        if (x == 1 || y == 1) {
            return special(x + y - 1, bound);
        }
        int max_idx_x = std::log(bound) / std::log(x);
        int max_idx_y = std::log(bound) / std::log(y);
        std::set<int> ret;
        for (int idx_x=0; idx_x<=max_idx_x; ++idx_x) {
            for (int idx_y=0; idx_y<=max_idx_y; ++idx_y) {
                int tmp = std::pow(x, idx_x) + std::pow(y, idx_y);
                if (tmp <= bound) {
                    ret.insert(tmp);
                }
            }
        }
        return std::vector<int>(ret.begin(), ret.end());
    }

    vector<int> special(int x, int bound) {
        if (x == 1) {
            if (bound < 2) {
                return {};
            } else {
                return {2};
            }
        }

        int tmp = 1;
        std::vector<int> ret;
        while (tmp+1 <= bound) {
            ret.push_back(tmp+1);
            tmp *= x;
        }
        return ret;
    }
};

int main() {
    auto ret = Solution().powerfulIntegers(1, 1, 0) ;
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
