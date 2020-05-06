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
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        const int R = matrix.size();
        const int C = matrix[0].size();
        int sr = 0;
        int sc = 0;
        for (; sc<C; ++sc) {
            int val = matrix[sr][sc];
            for (int r=sr, c=sc; r<R && c<C; ++r, ++c) {
                if (matrix[r][c] != val) {
                    return false;
                }
            }
        }

        sc = 0;
        sr = 1;
        for (; sr<R; ++sr) {
            int val = matrix[sr][sc];
            for (int r=sr, c=sc; r<R && c<C; ++r, ++c) {
                if (matrix[r][c] != val) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    return 0;
}

