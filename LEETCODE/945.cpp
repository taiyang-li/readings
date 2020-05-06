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
    int minDeletionSize(vector<string>& A) {
        const int R = A.size();
        const int C = A[0].size();
        int ret = 0;
        int r = 0;
        int c = 0;
        for (c=0; c<C; ++c) {
            for (r=0; r<R-1; ++r) {
                if (A[r][c] > A[r+1][c]) {
                    break;
                }
            }
            if (r != R-1) {
                ++ret;
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

