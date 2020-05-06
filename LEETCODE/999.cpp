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
    int numRookCaptures(vector<vector<char> >& board) {
        // find rook
        int r = 0;
        int c = 0;
        for (r=0; r<8; ++r) {
            for (c=0; c<8; ++c) {
                if (board[r][c] == 'R') {
                    break;
                }
            }
            if (board[r][c] == 'R') {
                break;
            }
        }
        int ret = 0;
        ret += detect(board, r, c, 0, 1);
        ret += detect(board, r, c, 0, -1);
        ret += detect(board, r, c, 1, 0);
        ret += detect(board, r, c, -1, 0);
        return ret;
    }

    int detect(vector<vector<char> >& board, int r, int c, int dr, int dc) {
        int ret = 0;
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c] == 'B') {
                break;
            } 

            if (board[r][c] == 'p') {
                ++ret;
                break;
            }
            r += dr;
            c += dc;
        }
        return ret;
    }
}; 

int main() {
    for (int i=0; i<1000; ++i) {
    // vector<vector<char> > board = {{'.','.','.','.','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'p','p','.','R','.','p','B','.'},{'.','.','.','.','.','.','.','.'},{'.','.','.','B','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'.','.','.','.','.','.','.','.'}};
    vector<vector<char> > board = {{'.','.','.','.','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'.','.','.','R','.','.','.','p'},{'.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.'}};
    std::cout << Solution().numRookCaptures(board) << std::endl;
    }
    return 0;
}

