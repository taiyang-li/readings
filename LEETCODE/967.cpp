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
using std::vector;

class Solution {
public:
    vector<int> numsSameConsecDiff(int N, int K) {
        _results.clear();
        dfs(0, N, K);
        return std::vector<int>(_results.begin(), _results.end());
    }

    void dfs(int curr, int left, int K) {
        if (left == 0) {
            _results.insert(curr);
            return;
        }

        if (curr == 0) {
            if (left == 1) {
                dfs(0, left-1, K);
            }
            for (int i=1; i<=9; ++i) {
                dfs(i, left-1, K);
            }
            return;
        }

        int ge = curr % 10;
        if (ge + K <= 9) {
            dfs(10*curr+ge+K, left-1, K);
        }
        if (ge - K >= 0) {
            dfs(10*curr+ge-K, left-1, K);
        }
    }
    
protected:
   std::set<int> _results;
};

int main() {
    int N = 3;
    int K = 1;
    auto ret = Solution().numsSameConsecDiff(N, K);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
