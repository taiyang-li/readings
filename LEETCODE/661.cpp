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
    vector<vector<int> > imageSmoother(vector<vector<int> >& M) {
        if (M.empty() || M[0].empty()) return {{}};
        const int row_num = M.size();
        const int col_num = M[0].size();
        std::vector<std::vector<int> > ret(row_num, std::vector<int>(col_num, 0));
        for (int row=0; row<row_num; ++row) {
            for (int col=0; col<col_num; ++col) {
                ret[row][col] = smooth(M, row_num, col_num, row, col);
            }
        }
        return ret;
    }

    inline int smooth(vector<vector<int> >& M, int row_num, int col_num, int row, int col) {
        int new_row = 0;
        int new_col = 0;
        int count = 0;
        int sum = 0;
        for (const auto& direction : _directions) {
            new_row = row + direction.first;
            new_col = col + direction.second;
            if (new_row < 0 || new_row >= row_num || new_col < 0 || new_col >= col_num) {
                continue;
            }
            count++;
            sum += M[new_row][new_col];
        }
        return sum/count;
    }

    static const std::vector<std::pair<int, int> > _directions;
};

const std::vector<std::pair<int, int> > Solution::_directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

int main() {
    std::vector<std::vector<int> > M = {{1,1,1}, {1,0,1}, {1,1,1}};
    auto ret = Solution().imageSmoother(M);
    for (const auto& vec: ret) {
        for (auto x : vec) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
