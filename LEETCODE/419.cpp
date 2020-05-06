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
    int countBattleships(vector<vector<char> >& board) {
        if (board.empty() || board[0].empty()) {
            return 0;
        }

        const int row_num = board.size();
        const int col_num = board[0].size();
        int ret = 0;
        for (int row=0; row<row_num; ++row) {
            int plus = 0;
            int minus = 0;
            for (int col=0; col<col_num; ++col) {
                if (board[row][col] == 'X') {
                    if (col == 0 || board[row][col-1] == '.') {
                        plus++;
                    }
                    if (row > 0 && board[row-1][col] == 'X') {
                        minus++;
                    }
                }
            }
            ret += plus - minus;
        }
        return ret;
    }
};

int main() {
    std::vector<std::vector<char> > board = {{'X', '.', '.', 'X'}, {'.', '.', '.', 'X'}, {'.', '.', '.', 'X'}};
    std::cout << Solution().countBattleships(board) << std::endl;
    return 0;
}
