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
    vector<vector<int>> flipAndInvertImage(vector<vector<int> >& A) {
        const int width = A[0].size();
        for (auto& line: A) {
            int i = 0;
            int j = width-1;
            for (; i<j; ++i, --j) {
                line[i] = 1 - line[i];
                line[j] = 1 - line[j];
                std::swap(line[i], line[j]);
            }
            if (i == j) {
                line[i] = 1 - line[i];
            }
        }
        return A;
    }
};

int main() {
    return 0;
}

