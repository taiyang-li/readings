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
#include <cmath>
using std::vector;
using std::string;

class Solution {
public:
    int surfaceArea(vector<vector<int> >& grid) {
        int ret = 0;
        const int R = grid.size();
        const int C = grid[0].size();
        for (int r=0; r<R; ++r) {
            for (int c=0; c<C; ++c) {
                if (grid[r][c] > 0) {
                    ret += 2;
                }
                if (r == 0) {
                    ret += grid[r][c];
                }
                if (c == 0) {
                    ret += grid[r][c];
                }
                ret += r == R-1 ? grid[r][c] : std::abs(grid[r][c] - grid[r+1][c]);
                ret += c == C-1 ? grid[r][c] : std::abs(grid[r][c] - grid[r][c+1]);
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

