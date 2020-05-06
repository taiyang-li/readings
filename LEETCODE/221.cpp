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
    int maximalSquare(vector<vector<char> >& matrix) {
        const int row_num = matrix.size(); 
        if (row_num == 0) return 0;
        const int col_num = matrix[0].size();
        if (col_num == 0) return 0;

        int ret = 0;
        std::vector<std::vector<int> > table(row_num, std::vector<int>(col_num, 0));
        for (int row=0; row<row_num; ++row) {
            table[row][0] = matrix[row][0] == '1' ? 1 : 0;
            ret = std::max(ret, table[row][0]);
        }
        for (int col=0; col<col_num; ++col) {
            table[0][col] = matrix[0][col] == '1' ? 1 : 0;
            ret = std::max(ret, table[0][col]);
        }
        for (int row=1; row<row_num; ++row) {
            for (int col=1; col<col_num; ++col) {
                bool none_zero = true;
                int max_size = std::min(row+1, col+1);
                int size = 1;
                while (size <= max_size) {
                    if (size == 1) {
                        none_zero = (matrix[row][col] == '1');
                    } else {
                        none_zero = table[row-1][col-1] >= size - 1 && 
                            table[row-size+1][col] >= 1 &&
                            table[row][col-size+1] >= 1;
                    }
                    if (! none_zero)  {
                        break;
                    }
                    size++;
                }
                table[row][col] = size-1;
                ret = std::max(ret, size-1);
            }
        }
        return ret * ret;
    }
};

int main() {
    /*
    std::vector<std::vector<char> > matrix = {
        {1,0,1,0,0},
        {1,0,1,1,1},
        {1,1,1,1,1},
        {1,0,0,1,0}
    };
    */
    std::vector<std::vector<char> > matrix =  {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    std::cout << Solution().maximalSquare(matrix) << std::endl;
    return 0;
}
