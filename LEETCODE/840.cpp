#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        const int row_num = grid.size();
        if (row_num < 3) return false;
        const int col_num = grid[0].size();
        if (col_num < 3) return false;

        int ret = 0;
        for (int i=1; i<row_num-1; ++i) {
            for (int j=1; j<col_num-1; ++j) {
                if (helper(grid, i, j)) {
                    ret++;
                }
            }
        }
        return ret;
    }

    bool helper(std::vector<std::vector<int> >& grid, int row, int col) {
        if (grid[row][col] != 5) return false;
        int row_sum[3] = {0};
        int col_sum[3] = {0};
        int dig_sum[2] = {0};
        int row_offset = 0;
        int col_offset = 0;
        for (int i=row-1; i<=row+1; ++i) {
            for (int j=col-1; j<=col+1; ++j) {
                if (grid[i][j] < 1 || grid[i][j] > 9) return false;
                row_offset = i - (row-1);
                col_offset = j - (col-1);
                row_sum[row_offset] += grid[i][j];
                col_sum[col_offset] += grid[i][j];
                if (row_offset == col_offset) {
                    dig_sum[0] += grid[i][j];
                }
                if (row_offset + col_offset == 2) {
                    dig_sum[1] += grid[i][j];
                }
            }
        }
        for (int x=0; x<3; ++x) {
            if (row_sum[x] != 15 || col_sum[x] != 15 || (x<2 && dig_sum[x] != 15)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    std::vector<std::vector<int> > grid = {{4,3,8,4}, {9,5,1,9}, {2,7,6,2}} ;
    std::cout << Solution().numMagicSquaresInside(grid) << std::endl;
    return 0;
}
