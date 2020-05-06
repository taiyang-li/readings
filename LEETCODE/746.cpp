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
    int minCostClimbingStairs(vector<int>& cost) {
        const int len = cost.size();
        std::vector<int> tb(len+1, 0);
        tb[0] = 0;
        tb[1] = 0;
        for (int i=2; i<=len; ++i) {
            tb[i] = std::min(tb[i-1] + cost[i-1], tb[i-2] + cost[i-2]);
        }
        return tb[len];
    }
};

int main() {
    return 0;
}

