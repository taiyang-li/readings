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
    bool judgeSquareSum(int c) {
        int N = std::sqrt(c/2.0);
        for (int n=0; n<=N; ++n) {
            int tmp = c - n*n;
            int m = std::sqrt(tmp);
            if (m * m == tmp) {
                return true;
            }
        }
        return false;
    }
};
int main() {
    return 0;
}

