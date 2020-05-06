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
    int smallestRangeI(vector<int>& A, int K) {
        auto max_val = *std::max_element(A.begin(), A.end());
        auto min_val = *std::min_element(A.begin(), A.end());
        return std::max(max_val-min_val-2*K, 0);
    }
};


int main() {
    return 0;
}

