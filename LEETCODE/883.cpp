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
    int projectionArea(vector<vector<int> >& grid) {
        int xy = 0;
        int yz = 0;
        int xz = 0;
        for (const auto& row: grid) {
            yz += *std::max_element(row.cbegin(), row.cend());
        }

        const int X = grid[0].size();
        const int Y = grid.size();
        for (int x=0; x<X; ++x) {
            int max_val = 0;
            for (int y=0; y<Y; ++y) {
                xy += grid[y][x] > 0 ? 1 : 0;
                max_val = std::max(max_val, grid[y][x]);
            }
            xz += max_val;
        } 
        return xy + yz + xz;
    }
};

int main() {
    std::vector<std::vector<int> > grid = {{2}};
    std::cout << Solution().projectionArea(grid) << std::endl;
    return 0;
}

