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
    int islandPerimeter(vector<vector<int> >& grid) {
        const int R = grid.size();
        const int C = grid[0].size();
        int ret = 0;
        for (int r=0; r<R; ++r) {
            for (int c=0; c<C; ++c) {
                if (grid[r][c] == 0) {
                    continue;
                }
                
                int cnt1 = 0;
                if (r > 0 && grid[r-1][c] == 1) ++cnt1;
                if (r < R-1 && grid[r+1][c] == 1) ++cnt1;
                if (c > 0 && grid[r][c-1] == 1) ++cnt1;
                if (c < C-1 && grid[r][c+1] == 1) ++cnt1;
                ret += 4 - cnt1;
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

