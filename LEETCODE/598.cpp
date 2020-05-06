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
    int maxCount(int m, int n, vector<vector<int> >& ops) {
        int min_m = m;
        int min_n = n;
        for (const auto& op: ops) {
            min_m = std::min(min_m, op[0]);
            min_n = std::min(min_n, op[1]);
        }
        return min_m * min_n;
    }
}; 

int main() {
    return 0;
}

