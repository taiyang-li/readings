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
        int orangesRotting(vector<vector<int> >& grid) {
            if (grid.empty() || grid[0].empty()) {
                return 0;
            }

            int total_fresh = 0;
            for (const auto& row: grid) {
                for (auto fruit: row) {
                    if (fruit == 1) {
                        total_fresh++;
                    }
                }
            }

            int total_rotten = 0;
            int rotten = 0;
            int minute = 0;
            while ((rotten = rot(grid)) > 0) {
                total_rotten += rotten;
                minute++;
            }
            return total_rotten == total_fresh ? minute : -1;
        }

        inline int rot(vector<vector<int> >& grid) {
            int ret = 0;
            vector<vector<int> > next = grid;
            int rows = next.size();
            int cols = next[0].size();
            for (int i=0; i<rows; ++i) {
                for (int j=0; j<cols; ++j) {
                    if (next[i][j] == 1) {
                        if ((i > 0 && grid[i-1][j] == 2) || (i < rows-1 && grid[i+1][j] == 2) 
                                || (j > 0 && grid[i][j-1] == 2) || (j < cols-1 && grid[i][j+1] == 2)) {
                            next[i][j] = 2;
                            ret++;
                        }
                    }
                }
            }
            grid.swap(next);
            return ret;
        }
};

int main() {
    std::vector<std::vector<int> > grid = {{2,1,1},{1,1,0},{0,1,1}};
    std::cout << Solution().orangesRotting(grid) << std::endl;
    return 0;
}
