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
    void gameOfLife(std::vector<std::vector<int>>& board) {
        int count = 0;
        for (int i=0; i<int(board.size()); ++i) {
            for (int j=0; j<int(board[0].size()); ++j) {
                count = 0;
                for (int x=std::max(i-1, 0); x<=std::min(i+1, int(board.size())-1); ++x) {
                    for (int y=std::max(j-1, 0); y<=std::min(j+1, int(board[0].size())-1); ++y) {
                        if ((x != i || y != j) && (board[x][y] & 1)) {
                            count++;
                        }
                    }
                }

                if ((board[i][j] & 1) && (count < 2 || count > 3)) {
                    board[i][j] &= ~2;
                } else if (! (board[i][j] & 1) && count == 3) {
                    board[i][j] |= 2;
                } else {
                    board[i][j] |= (board[i][j] & 1) << 1;
                }
            }
        }

        for (int i=0; i<int(board.size()); ++i) {
            for (int j=0; j<int(board[0].size()); ++j) {
                board[i][j] >>= 1;
            }
        }
    }
};

int main() {
    std::vector<std::vector<int> > board = { {0,1,0}, {0,0,1}, {1,1,1}, {0,0,0} };
    Solution().gameOfLife(board);
    for (auto& x: board) {
        for (auto y: x) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
