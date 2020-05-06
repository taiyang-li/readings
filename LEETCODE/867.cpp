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
    vector<vector<int> > transpose(vector<vector<int> >& A) {
        const int R = A.size();
        const int C = A[0].size();
        std::vector<std::vector<int> > ret(C, std::vector<int>(R, 0));
        for (int i=0; i<C; ++i) {
            for (int j=0; j<R; ++j) {
                ret[i][j] = A[j][i];
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

