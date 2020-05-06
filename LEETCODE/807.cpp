#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int> >& grid) {
        if (grid.empty()) return 0;
        const int row_num = grid.size();
        if (grid[0].empty()) return 0;
        const int col_num = grid[0].size();
        
        std::vector<int> row_max(row_num, 0);
        for (int row=0; row<row_num; ++row) {
            row_max[row] = *std::max_element(grid[row].begin(), grid[row].end());
        }

        std::vector<int> col_max(col_num, 0);
        for (int col=0; col<col_num; ++col) {
            col_max[col] = -1;
            for (int row=0; row<row_num; ++row) {
                col_max[col] = std::max(col_max[col], grid[row][col]);
            }
        }

        int ret = 0;
        for (int row=0; row<row_num; ++row) {
            for (int col=0; col<col_num; ++col) {
                ret += std::max(std::min(row_max[row], col_max[col]) - grid[row][col], 0);
            }
        }
        return ret;
    }
};

int main() {
    std::vector<std::vector<int> > grid = {{3,0,8,4},{2,4,5,7},{9,2,6,3},{0,3,1,0}};
    std::cout << Solution().maxIncreaseKeepingSkyline(grid) << std::endl;
    return 0;
}
